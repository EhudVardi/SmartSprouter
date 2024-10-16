#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "BaseManager.h"
#include <string>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "GUI/GuiElement.h"
#include "GUI/Label.h"
#include "GUI/NamedValue.h"
#include "GUI/TypedNameValue.h"
#include "GUI/Page.h"
#include "GUI/EditState.h"
#include "GUI/FontSize.h"


// Define OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used on ESP32
#define SCREEN_ADDRESS 0x3C // Change if needed


// Define SDA and SCL pins for I2C
#define SDA_PIN 25        // Change to your desired SDA pin
#define SCL_PIN 26        // Change to your desired SCL pin




class DisplayManager : public BaseManager {
private:
    
    TwoWire i2cwires = TwoWire(0);

    Adafruit_SSD1306 display;

    Page myPage;

Label myLabel;
NamedValueInt intValue;
NamedValueFloat floatValue;
NamedValueFloat percentValue;

public:
    DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &i2cwires, OLED_RESET), 
    myLabel(0, 0, "Status", FontSize::Medium), 
    intValue(0, 16, "Count", FontSize::Small), 
    floatValue(0, 26, "Temperature", FontSize::Small),  
    percentValue(0, 36, "Humidity", FontSize::Small) {} // Initialize in the constructor

    bool initialize() override;
    void showPage(const std::string& page);
    void updateLabel(const std::string& label, const std::string& value);

    void refresh();
};

#endif // DISPLAY_MANAGER_H
