#include "SystemContext/DisplayManager.h"
#include <iostream>

bool DisplayManager::initialize() {
    
    displayHandler = new LcdDisplayHandler(LCD_SDA_PIN, LCD_SCL_PIN);

    // Clear the display buffer
    displayHandler->GetDisplayObject().clearDisplay();
     
    // Set initial values
    intValue.SetValue(42);     // Example integer value
    floatValue.SetValue(25.3); // Example float value
    percentValue.SetValue(15.52);
    myRange.SetMinValue(5);
    myRange.SetMaxValue(20);
    myRangeTemp.SetMinValue(20);
    myRangeTemp.SetMaxValue(50);

    floatValue.SetEditState(NamedValueEditState::Entered);

    // Add elements to the page
    myPage.AddElement(&myLabel);
    myPage.AddElement(&intValue);
    myPage.AddElement(&floatValue);
    myPage.AddElement(&percentValue);
    //myPage.AddElement(&myCenteredLabel);
    myPage.AddElement(&myRange);
    myPage.AddElement(&myRangeTemp);


    return true;
}

void DisplayManager::showPage(const std::string& page) {
    std::cout << "Displaying: " << page << std::endl;
}

void DisplayManager::updateLabel(const std::string& label, const std::string& value) {
    std::cout << "Updating " << label << " to " << value << std::endl;
}

void DisplayManager::refresh() {

    if (displayHandler != nullptr) {
        myPage.Draw(*displayHandler);
    } else {
        Serial.println("Error: displayHandler is nullptr!");
    }

    // Example: Modify the values dynamically (can be replaced by actual sensor input)
    static int count = 42;
    static float temp = 25.3;
    static float percent = 0.1;
    
    count += 1;
    temp += 0.1;
    percent += 0.65;
    
    intValue.SetValue(count);
    floatValue.SetValue(temp);

    NamedValueEditState intstate = intValue.GetEditState();
    intValue.SetEditState(intstate == NamedValueEditState::None ? NamedValueEditState::Selected : (intstate == NamedValueEditState::Selected ? NamedValueEditState::Entered : NamedValueEditState::None));

    percentValue.SetValue(percent);


    NamedRangeEditState percentRangeState = myRange.GetEditState();
    myRange.SetEditState(percentRangeState == NamedRangeEditState::None ? NamedRangeEditState::Selected : (percentRangeState == NamedRangeEditState::Selected ? NamedRangeEditState::EnteredMin : (percentRangeState == NamedRangeEditState::EnteredMin ? NamedRangeEditState::EnteredMax : NamedRangeEditState::None)));

    myRange.SetMinValue(percent+50);
    myRange.SetMaxValue(percent+70);


    myRangeTemp.SetMinValue(temp+25);
    myRangeTemp.SetMaxValue(temp+40);
}
