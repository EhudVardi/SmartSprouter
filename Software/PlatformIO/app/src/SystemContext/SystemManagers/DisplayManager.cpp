#include "SystemContext/SystemManagers/DisplayManager.h"
#include "Data/Log.h"
#include <iostream>

DisplayManager::DisplayManager() {

    auto appPageAbout = std::make_shared<PageAppAbout>();
    auto appPageError = std::make_shared<PageAppError>();
    auto appPageAbort = std::make_shared<PageAppAbort>();
    auto appPageIdle = std::make_shared<PageAppIdle>();
    auto appPageRun = std::make_shared<PageAppRun>();
    auto appPageSetup = std::make_shared<PageAppSetup>();
    auto appPageDiag = std::make_shared<PageAppDiag>();

    addPage(Pages::About, appPageAbout);
    addPage(Pages::Error, appPageError);
    addPage(Pages::Abort, appPageAbort);
    addPage(Pages::Idle, appPageIdle);
    addPage(Pages::Run, appPageRun);
    addPage(Pages::Setup, appPageSetup);
    addPage(Pages::Diag, appPageDiag);
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
        currentPage->InvalidatePage();
        
    } else {
        log("Page " + String(EnumHelpers::PagesHelper.ToString(pageEnum)) + " not found!", LogType::Error);
    }
}

std::shared_ptr<PageBase> DisplayManager::getPage(Pages pageEnum) {
    return pageMap[pageEnum];
}

void DisplayManager::refresh() {
    if (displayHandler != nullptr && currentPage != nullptr)
        currentPage->Draw(*displayHandler);
}
