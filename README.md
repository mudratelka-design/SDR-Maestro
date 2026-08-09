# SDR Maestro — Commit 11 / v0.3.0

ESP32-S3 BLE keyboard controller: 5 rotary encoders × 4 events each
(turnRight, turnLeft, short press, long press), sent as BLE HID keyboard /
media keys. No external libraries required — everything (BLE, WiFi,
WebServer, Preferences/NVS) comes bundled with the ESP32 Arduino core.

## Build target

Arduino IDE 2.x, ESP32 board package (Arduino core) 3.3.11, board
"ESP32S3 Dev Module" (or your specific N16R8 board entry).

## What's new in commit 11

- **Web config page.** No more editing the sketch to change what a button
  does. Connect to the device's own WiFi network and use a form.
- **5 profiles, one per encoder.** Profile 0 ("OpenWebRX") is the built-in
  example from `OpenWebRXProfile.cpp`. Profiles 1–4 start empty until you
  define them.
- **Boot-time profile pick.** Short-press an encoder within 5 seconds of
  power-on to make that encoder's profile active for the session.
- **Persistent storage.** Anything saved from the web page is written to
  flash (NVS) and reloaded on every boot.

## Using the config page

1. Power on the device.
2. Within 5 minutes, connect to WiFi network **`SDR Maestro`**, password
   **`aaaaaaaa`** (both set in `Config.h`).
3. Open `http://192.168.4.1/` in a browser.
4. Pick **Edit** on a profile to fill in its 20 fields (5 encoders × 4
   events), or **Activate** to switch which profile is currently live.
5. If nobody is connected 5 minutes after boot, the access point turns
   itself off automatically (to limit how long the device is a joinable
   WiFi network). It comes back on the next time you power-cycle.

### Field format

Each of the 20 boxes on a profile's edit page accepts:

| Format               | Meaning                                   | Example            |
|-----------------------|--------------------------------------------|---------------------|
| `NONE` (or blank)     | No action                                  | `NONE`              |
| `KEY:<name>`          | A named HID key                            | `KEY:UP_ARROW`      |
| `KEY:<name>+<mod>`    | Key + modifier(s), `+`-separated           | `KEY:TAB+SHIFT`     |
| `KEY:0x<hex>`         | Raw HID keycode                            | `KEY:0x29`          |
| `CHAR:<letter>`       | A single typed character                   | `CHAR:m`            |
| `MEDIA:<name>`        | A consumer/media key                       | `MEDIA:VOLUME_UP`   |
| `MEDIA:0x<hex>`       | Raw media usage code                       | `MEDIA:0xE9`        |

Recognized key names, media names, and modifier names are listed at the
top of `ActionCodec.cpp`. Anything unrecognized is treated as `NONE`
(never crashes the page — just does nothing until corrected).

## Boot-time profile selection

- No press in the first 5 seconds → profile 0 (OpenWebRX) loads, same as
  before this feature existed.
- Short-press encoder *N*'s button in that window → profile *N* becomes
  active for this session (not saved as the new default — next boot
  starts at profile 0 again unless you press during that window).

## Files

| File | Role |
|---|---|
| `Config.h` | Pins, timings, WiFi AP SSID/password, profile count |
| `ProfileManager.*` | Holds all profiles' bindings, tracks which is active |
| `StorageManager.*` | NVS (flash) persistence per profile |
| `ActionCodec.*` | Text ⇄ `KeyAction` conversion for the web form |
| `WebConfigServer.*` | AP + HTTP server + page handlers |
| `OpenWebRXProfile.*` | Profile 0's compiled-in default bindings |
| `BleHidKeyboard.*` | BLE HID keyboard/media-key transmitter (core BLE only) |
| `EncoderManager.*` / `ButtonManager.*` | Quadrature decode / debounce+long-press |
| `App.*` | Wires everything together; boot profile-selection window |
