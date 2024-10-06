#include "DisplayManager.h"
#include <iostream>

void DisplayManager::showPage(const std::string& page) {
    std::cout << "Displaying: " << page << std::endl;
}

void DisplayManager::updateLabel(const std::string& label, const std::string& value) {
    std::cout << "Updating " << label << " to " << value << std::endl;
}
