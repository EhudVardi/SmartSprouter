#include "SystemContext/DisplayManager.h"
#include <iostream>

bool DisplayManager::initialize() {

    i2cwires.begin(SDA_PIN, SCL_PIN);
    
    // Initialize the OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Halt the program if display init fails
    }

    // Clear the display buffer
    display.clearDisplay();
    
    //display.setTextColor(SSD1306_WHITE);
     
    // Set initial values
    intValue.SetValue(42);     // Example integer value
    floatValue.SetValue(25.3); // Example float value
    percentValue.SetValue(15.52);

    floatValue.SetEditState(EditState::Entered);

    // Add elements to the page
    myPage.AddElement(&myLabel);
    myPage.AddElement(&intValue);
    myPage.AddElement(&floatValue);
    myPage.AddElement(&percentValue);


    return true;
}

void DisplayManager::showPage(const std::string& page) {
    std::cout << "Displaying: " << page << std::endl;
}

void DisplayManager::updateLabel(const std::string& label, const std::string& value) {
    std::cout << "Updating " << label << " to " << value << std::endl;
}

void DisplayManager::refresh() {

        // Update display contents
    myPage.Draw(display);

    // Example: Modify the values dynamically (can be replaced by actual sensor input)
    static int count = 42;
    static float temp = 25.3;
    static float percent = 0.1;
    
    count += 1;
    temp += 0.1;
    percent += 0.65;
    
    intValue.SetValue(count);
    floatValue.SetValue(temp);

    EditState intstate = intValue.GetEditState();
    intValue.SetEditState(intstate == EditState::None ? EditState::Selected : (intstate == EditState::Selected ? EditState::Entered : EditState::None));

    percentValue.SetValue(percent);

}
