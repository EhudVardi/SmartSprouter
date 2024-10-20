#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "BaseManager.h"

#include <memory>
#include <unordered_map>

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
#include "GUI/Pages.h"


class DisplayManager : public BaseManager {
private:
    LcdDisplayHandler* displayHandler = nullptr;

    std::shared_ptr<PageBase> currentPage;
    std::unordered_map<Pages, std::shared_ptr<PageBase>> pageMap; // Store states

public:
    DisplayManager();

    bool initialize() override;

    void addPage(Pages pageEnum, std::shared_ptr<PageBase> page);

    void changePage(Pages pageEnum);

    void refresh();
};

#endif // DISPLAY_MANAGER_H
