#ifndef LCD_DISPLAY_HANDLER_H
#define LCD_DISPLAY_HANDLER_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LcdDisplayProperties.h"

class LcdDisplayHandler {

private:
    TwoWire i2cwires = TwoWire(0); //I2C bus #0
    Adafruit_SSD1306 display;

public:
    LcdDisplayHandler(int sda_pin, int scl_pin) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &i2cwires, OLED_RESET) {

        i2cwires.begin(sda_pin, scl_pin);

        // Initialize the OLED display
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Address 0x3C for 128x64
            Serial.println(F("SSD1306 allocation failed"));
            for (;;); // Halt the program if display init fails
        }
    }

    Adafruit_SSD1306& GetDisplayObject() {
        return display;
    }

    // Prevent copying and assignment for this class
    LcdDisplayHandler(const LcdDisplayHandler&) = delete;  // No copy constructor
    LcdDisplayHandler& operator=(const LcdDisplayHandler&) = delete;  // No copy assignment

};

#endif // LCD_DISPLAY_HANDLER_H