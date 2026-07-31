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
