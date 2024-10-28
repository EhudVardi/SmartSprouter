# Goal
build a controlled automatic sprouter that can monitor progress of a long sprouting process, activate moisture devices, have a display and input hw to control the process.
it shall sense the moisture level and apply moisture as needed
it should sense temperature and may control it with some kind of device
it may take photos for hyperlapse video of the sprouting proceedure


# Configuration



# Hardware
## Pinout
| Pin Name | Pin Number |
| -------- | ---------- |
| DIGITAL_OUTPUT_RELAY1_PIN | 16 |
| DIGITAL_OUTPUT_RELAY2_PIN | 17 |
| BUTTON_BACK_PIN | 12 |
| ROTARY_ENCODER_MAIN_A_PIN | 18 |
| ROTARY_ENCODER_MAIN_B_PIN | 19 |
| ROTARY_ENCODER_MAIN_BUTTON_PIN | 21 |
| SENSOR_DHT11_PIN | 4 |
| LCD_SDA_PIN | 25 |
| LCD_SCL_PIN | 26 |

## Notes
### ESP32 relay board pinout
reset into user app - press EN button\
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


# Resources

## State Machine fundementals
https://drawio-app.com/blog/uml-state-diagrams-with-draw-io/
https://statesmith.github.io/fundamentals-1/
https://github.com/StateSmith/StateSmith-drawio-plugin/wiki/How-to-Use
https://www.lucidchart.com/pages/uml-state-machine-diagram
https://sparxsystems.com/resources/tutorials/uml2/state-diagram.html
