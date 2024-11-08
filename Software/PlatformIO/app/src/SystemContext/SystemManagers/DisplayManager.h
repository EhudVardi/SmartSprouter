#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <memory>
#include <unordered_map>
#include "BaseManager.h"
#include "HardwareAbstraction/LcdDisplayHandler.h"
#include "GUI/Pages/PageBase.h"
#include "GUI/Pages/PageAppBase.h"
#include "GUI/Pages/PageAppAbout.h"
#include "GUI/Pages/PageAppError.h"
#include "GUI/Pages/PageAppAbort.h"
#include "GUI/Pages/PageAppIdle.h"
#include "GUI/Pages/PageAppRun.h"
#include "GUI/Pages/PageAppSetup.h"
#include "GUI/Pages/PageAppDiag.h"
#include "GUI/Pages/Pages.h"


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

    std::shared_ptr<PageBase> getPage(Pages pageEnum);
    
    template <typename T>
    std::shared_ptr<T> getPageAs(Pages pageEnum) {
        auto page = pageMap[pageEnum];
        if (page && page->getType() == pageEnum) {
            return std::static_pointer_cast<T>(page);
        }
        return nullptr;
    }

    void refresh();
};

#endif // DISPLAY_MANAGER_H
