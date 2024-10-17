#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "BaseManager.h"
#include <string>

#include "HardwareAbstraction/LcdDisplayHandler.h"
#include "SystemContext/DisplayPins.h"

#include "GUI/GuiElement.h"
#include "GUI/Label.h"
#include "GUI/CenteredLabel.h"
#include "GUI/NamedValue.h"
#include "GUI/TypedNameValue.h"
#include "GUI/Page.h"
#include "GUI/EditState.h"
#include "GUI/FontSize.h"


class DisplayManager : public BaseManager {
private:

    LcdDisplayHandler* displayHandler = nullptr;

    Page myPage;
    
    Label myLabel;
    NamedValueInt intValue;
    NamedValueFloat floatValue;
    NamedValueFloat percentValue;
    CenteredLabel myCenteredLabel;

public:
    DisplayManager() :
    myLabel(0, 0, "Status", FontSize::Medium), 
    intValue(0, 16, "Count", FontSize::Small), 
    floatValue(0, 26, "Temperature", FontSize::Small),  
    percentValue(0, 36, "Humidity", FontSize::Small), 
    myCenteredLabel(40, "Centered", FontSize::Medium) {} // Initialize in the constructor

    bool initialize() override;
    void showPage(const std::string& page);
    void updateLabel(const std::string& label, const std::string& value);

    void refresh();
};

#endif // DISPLAY_MANAGER_H
