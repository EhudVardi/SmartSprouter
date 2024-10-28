#ifndef APPLICATION_CONFIG_H
#define APPLICATION_CONFIG_H

//TIME
extern const int utcOffsetHours;

//NETWORK
extern const char* ssid;
extern const char* password;
extern const char* ntpServerUrl;
extern const int ntpPort;

//SYSTEM HARDWARE PINS
// ACTUATOR_PINS
#define DIGITAL_OUTPUT_RELAY1_PIN 16
#define DIGITAL_OUTPUT_RELAY2_PIN 17
#define DIGITAL_OUTPUT_RELAY1_NAME "relay1"
#define DIGITAL_OUTPUT_RELAY2_NAME "relay2"

// DISPLAY_PINS
#define LCD_SDA_PIN 25 
#define LCD_SCL_PIN 26

// INPUT_PINS
#define BUTTON_BACK_PIN 12
#define ROTARY_ENCODER_MAIN_A_PIN 18
#define ROTARY_ENCODER_MAIN_B_PIN 19
#define ROTARY_ENCODER_MAIN_BUTTON_PIN 21

// SENSOR_PINS
#define SENSOR_DHT11_PIN 4

// RTC_PINS
#define RTC_SDA_PIN 25 
#define RTC_SCL_PIN 26

#endif // APPLICATION_CONFIG_H