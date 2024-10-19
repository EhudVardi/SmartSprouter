#include "SystemContext/DisplayManager.h"
#include <iostream>

bool DisplayManager::initialize() {
    
    displayHandler = new LcdDisplayHandler(LCD_SDA_PIN, LCD_SCL_PIN);

    displayHandler->GetDisplayObject().clearDisplay();

    return true;
}

void DisplayManager::showPage(const std::string& page) {
    std::cout << "Displaying: " << page << std::endl;
}

void DisplayManager::updateLabel(const std::string& label, const std::string& value) {
    std::cout << "Updating " << label << " to " << value << std::endl;
}

void DisplayManager::refresh() {
    
}
