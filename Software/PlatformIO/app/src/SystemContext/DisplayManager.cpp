#include "SystemContext/DisplayManager.h"
#include <iostream>

DisplayManager::DisplayManager() {

    auto appPageAbout = std::make_shared<PageAppAbout>();
    auto appPageError = std::make_shared<PageAppError>();
    auto appPageAbort = std::make_shared<PageAppAbort>();
    auto appPageIdle = std::make_shared<PageAppIdle>();
    auto appPageRun = std::make_shared<PageAppRun>();
    auto appPageSetup = std::make_shared<PageAppSetup>();

    addPage(Pages::About, appPageAbout);
    addPage(Pages::Error, appPageError);
    addPage(Pages::Abort, appPageAbort);
    addPage(Pages::Idle, appPageIdle);
    addPage(Pages::Run, appPageRun);
    addPage(Pages::Setup, appPageSetup);
}

bool DisplayManager::initialize() {
    
    displayHandler = new LcdDisplayHandler(LCD_SDA_PIN, LCD_SCL_PIN);

    displayHandler->GetDisplayObject().clearDisplay();
    displayHandler->GetDisplayObject().display();

    return true;
}

void DisplayManager::addPage(Pages pageEnum, std::shared_ptr<PageBase> page) {
    pageMap[pageEnum] = page;
}

void DisplayManager::changePage(Pages pageEnum) {
    auto newPage = pageMap.find(pageEnum);
    if (newPage != pageMap.end()) {

        displayHandler->GetDisplayObject().clearDisplay();
        currentPage = newPage->second;
        
    } else {
        std::cerr << "Page " << Pages_ToString(pageEnum) << " not found!" << std::endl;
    }
}

void DisplayManager::refresh() {
    static int temp = 0;
    temp++;
    if (!(temp % 1000)) {
        if (displayHandler != nullptr && currentPage != nullptr)
            currentPage->Draw(*displayHandler);
    }
}
