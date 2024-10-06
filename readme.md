# Goal
build a controlled automatic sprouter that can monitor progress of a long sprouting process, activate moisture devices, have a display and input hw to control the process.
it shall sense the moisture level and apply moisture as needed
it should sense temperature and may control it with some kind of device
it may take photos for hyperlapse video of the sprouting proceedure


# Configuration



# Hardware

## Notes

### ESP32 relay board
relay pins - 16 & 17

reset into user app - press EN button.

reset into bootloader - press and hold EN, press and hold I00, release EN, release I00


# Software 

## notes 

### PlatformIO
An embedded platform within VSCode
https://platformio.org/

#### vscode vertical selection
Alt+Shift+ mouse drag

#### serial comm with board 
on project ini file, set serial port baudrate with:
'monitor_speed = 115200'
