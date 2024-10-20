#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "BaseManager.h"
#include <string>

#include "HardwareAbstraction/LcdDisplayHandler.h"
#include "SystemContext/DisplayPins.h"

#include "GUI/PageBase.h"
#include "GUI/PageAppBase.h"
#include "GUI/PageAppAbout.h"
#include "GUI/PageAppError.h"
#include "GUI/PageAppAbort.h"
#include "GUI/PageAppIdle.h"
#include "GUI/PageAppRun.h"
#include "GUI/PageAppSetup.h"


class DisplayManager : public BaseManager {
private:

    LcdDisplayHandler* displayHandler = nullptr;

    PageAppAbout appPageAbout;
    PageAppError appPageError;
    PageAppAbort appPageAbort;
    PageAppIdle appPageIdle;
    PageAppRun appPageRun;
    PageAppSetup appPageSetup;

public:
    DisplayManager() {}

    bool initialize() override;
    void showPage(const std::string& page);
    void updateLabel(const std::string& label, const std::string& value);

    void refresh();
};

#endif // DISPLAY_MANAGER_H
