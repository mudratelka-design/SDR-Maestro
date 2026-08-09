//=============================================================================
// File: BleHidKeyboard.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================

#include "BleHidKeyboard.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLEHIDDevice.h>
#include <BLE2902.h>

namespace
{
    constexpr uint8_t REPORT_ID_KEYBOARD   = 0x01;
    constexpr uint8_t REPORT_ID_MEDIA_KEYS = 0x02;

    // Combined boot-keyboard + consumer-control HID report descriptor.
    // Report 1: standard 8-byte keyboard report (modifier, reserved, 6 keys).
    // Report 2: 16-bit consumer-control usage code (volume/mute/etc.).
    const uint8_t HID_REPORT_DESCRIPTOR[] =
    {
        0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,             // USAGE (Keyboard)
        0xA1, 0x01,             // COLLECTION (Application)
        0x85, REPORT_ID_KEYBOARD,
        0x05, 0x07,              //   USAGE_PAGE (Kbrd/Keypad)
        0x19, 0xE0,              //   USAGE_MINIMUM (0xE0)
        0x29, 0xE7,              //   USAGE_MAXIMUM (0xE7)
        0x15, 0x00,              //   LOGICAL_MINIMUM (0)
        0x25, 0x01,              //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,              //   REPORT_SIZE (1)
        0x95, 0x08,              //   REPORT_COUNT (8)   ; modifier byte
        0x81, 0x02,              //   INPUT (Data,Var,Abs)
        0x95, 0x01,              //   REPORT_COUNT (1)
        0x75, 0x08,              //   REPORT_SIZE (8)    ; reserved byte
        0x81, 0x01,              //   INPUT (Const,Array,Abs)
        0x95, 0x06,              //   REPORT_COUNT (6)   ; up to 6 keys
        0x75, 0x08,              //   REPORT_SIZE (8)
        0x15, 0x00,              //   LOGICAL_MINIMUM (0)
        0x25, 0x65,              //   LOGICAL_MAXIMUM (101)
        0x05, 0x07,              //   USAGE_PAGE (Kbrd/Keypad)
        0x19, 0x00,              //   USAGE_MINIMUM (0)
        0x29, 0x65,              //   USAGE_MAXIMUM (101)
        0x81, 0x00,              //   INPUT (Data,Array,Abs)
        0xC0,                    // END_COLLECTION

        0x05, 0x0C,              // USAGE_PAGE (Consumer)
        0x09, 0x01,              // USAGE (Consumer Control)
        0xA1, 0x01,              // COLLECTION (Application)
        0x85, REPORT_ID_MEDIA_KEYS,
        0x15, 0x00,              //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x03,        //   LOGICAL_MAXIMUM (1023)
        0x19, 0x00,              //   USAGE_MINIMUM (0)
        0x2A, 0xFF, 0x03,        //   USAGE_MAXIMUM (1023)
        0x75, 0x10,              //   REPORT_SIZE (16)
        0x95, 0x01,              //   REPORT_COUNT (1)
        0x81, 0x00,              //   INPUT (Data,Array,Abs)
        0xC0                     // END_COLLECTION
    };
}

// Bridges BLE connection events back onto the owning BleHidKeyboard.
class HidServerCallbacks : public BLEServerCallbacks
{
public:
    explicit HidServerCallbacks(BleHidKeyboard* owner) : owner(owner) {}

    void onConnect(BLEServer* /*pServer*/)
    {
        owner->setConnected(true);
    }

    void onDisconnect(BLEServer* /*pServer*/)
    {
        owner->setConnected(false);

        // A BLE peripheral stops advertising once connected; restart it so
        // the host (or another host) can reconnect after this disconnect.
        BLEDevice::startAdvertising();
    }

private:
    BleHidKeyboard* owner;
};

void BleHidKeyboard::begin(const char* deviceName, const char* manufacturer, uint8_t batteryLevel)
{
    BLEDevice::init(deviceName);

    BLEServer* server = BLEDevice::createServer();
    server->setCallbacks(new HidServerCallbacks(this));

    BLEHIDDevice* hid = new BLEHIDDevice(server);

    hid->manufacturer(manufacturer);
    hid->pnp(0x02, 0x303A, 0x0002, 0x0100); // 0x303A = Espressif's USB VID
    hid->hidInfo(0x00, 0x01);

    keyboardReport = hid->inputReport(REPORT_ID_KEYBOARD);
    mediaReport    = hid->inputReport(REPORT_ID_MEDIA_KEYS);

    hid->reportMap(const_cast<uint8_t*>(HID_REPORT_DESCRIPTOR), sizeof(HID_REPORT_DESCRIPTOR));
    hid->startServices();
    hid->setBatteryLevel(batteryLevel);

    BLEAdvertising* advertising = server->getAdvertising();
    advertising->setAppearance(HID_KEYBOARD);
    advertising->addServiceUUID(hid->hidService()->getUUID());
    advertising->setScanResponse(true);

    BLEDevice::startAdvertising();
}

bool BleHidKeyboard::isConnected() const
{
    return connected;
}

void BleHidKeyboard::setConnected(bool state)
{
    connected = state;
}

void BleHidKeyboard::sendKey(uint8_t keyCode, uint8_t modifier)
{
    if (!connected || keyboardReport == nullptr)
    {
        return;
    }

    uint8_t press[8] = { 0 };
    press[0] = modifier;
    press[2] = keyCode;

    keyboardReport->setValue(press, sizeof(press));
    keyboardReport->notify();

    delay(8); // give the host time to register press-then-release as two events

    uint8_t release[8] = { 0 };
    keyboardReport->setValue(release, sizeof(release));
    keyboardReport->notify();
}

void BleHidKeyboard::sendMediaKey(uint8_t usageCode)
{
    if (!connected || mediaReport == nullptr)
    {
        return;
    }

    uint8_t press[2] = { usageCode, 0x00 };
    mediaReport->setValue(press, sizeof(press));
    mediaReport->notify();

    delay(8);

    uint8_t release[2] = { 0x00, 0x00 };
    mediaReport->setValue(release, sizeof(release));
    mediaReport->notify();
}

KeyAction HidKey::fromChar(char c)
{
    KeyAction action;

    if (c >= 'a' && c <= 'z')
    {
        action.type = KeyType::Key;
        action.key = static_cast<uint8_t>(0x04 + (c - 'a'));
    }
    else if (c >= 'A' && c <= 'Z')
    {
        action.type = KeyType::Key;
        action.key = static_cast<uint8_t>(0x04 + (c - 'A'));
        action.modifier = LEFT_SHIFT;
    }
    else if (c >= '1' && c <= '9')
    {
        action.type = KeyType::Key;
        action.key = static_cast<uint8_t>(0x1E + (c - '1'));
    }
    else if (c == '0')
    {
        action.type = KeyType::Key;
        action.key = 0x27;
    }
    else if (c == ' ')
    {
        action.type = KeyType::Key;
        action.key = SPACE;
    }
    // Unsupported character: action.type stays KeyType::None.

    return action;
}
