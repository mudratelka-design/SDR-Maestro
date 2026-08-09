# CHANGELOG.md

# Changelog

## Commit 6

### Added

- Hardware configuration for 5 rotary encoders.
- Centralized GPIO configuration in `Config.h`.
- Support for multiple encoders.
- Button debounce.
- Long press detection infrastructure.
- Encoder identification added to events.

### Notes

- Long press events are generated but are not yet assigned to any action.
- Encoder modules are configured for external onboard pull-up resistors.






## Commit 7

### Fixed

- Unified include hierarchy.
- Fixed global instance declarations.
- Fixed build dependencies.
- Fixed module initialization order.
- Fixed configuration sharing.
- Fixed queue visibility.
- Fixed profile access.
- Fixed HID attachment.

### Ready

- ESP32 Arduino Core 3.3.11
- Five rotary encoders
- Bluetooth HID
- First hardware compilation
- First hardware upload



## Commit 9 
###changes vs. the "fixed" skeleton this was based on:
  
  - Removed the dependency on the external "ESP32 BLE Keyboard" library
    (unmaintained, doesn't compile on ESP32 core 3.x). BLE HID keyboard +
    media-key support is now implemented directly on top of the BLE
    classes bundled with ESP32 Arduino core 3.x itself - see
    BleHidKeyboard.h/.cpp. Nothing extra to install.
  - Reworked the action/profile pipeline: each of the 5 encoders x 4
    events (turnRight, turnLeft, short press, long press) now maps
    directly to a KeyAction (a HID key or media key) via
    OpenWebRXProfile.cpp, instead of going through an intermediate
    "ActionType" enum that only had a few cases wired up in HIDManager.
  - Fixed ButtonManager double-firing both the short-press AND the
    long-press action on every long hold.
  - Reworked EncoderManager to decode both quadrature pins with a
    transition table (rejects bounce, counts full detents) instead of
    only watching pin A.
  - Logger no longer blocks forever in setup() waiting for a USB serial
    monitor that may never attach.

	
##Commit 10

  - Fixed a boot-loop crash (Guru Meditation Error: LoadProhibited) in
    BleHidKeyboard::begin(). The single-argument hid->manufacturer(name)
    setter dereferences a BLEHIDDevice member that the ESP32 core's own
    BLEHIDDevice constructor never initializes; only the no-argument
    hid->manufacturer() getter actually creates that characteristic.
    Fixed by calling the getter first: hid->manufacturer()->setValue(name).