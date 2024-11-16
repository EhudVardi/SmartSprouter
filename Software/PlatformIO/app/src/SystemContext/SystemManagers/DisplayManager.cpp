#include "DisplayManager.h"
#include "Data/Log/Log.h"

DisplayManager::DisplayManager() {

    auto appPageAbout = std::make_shared<PageAppAbout>();
    auto appPageError = std::make_shared<PageAppError>();
    auto appPageAbort = std::make_shared<PageAppAbort>();
    auto appPageIdle = std::make_shared<PageAppIdle>();
    auto appPageRun = std::make_shared<PageAppRun>();
    auto appPageSetup = std::make_shared<PageAppSetup>();
    auto appPageDiag = std::make_shared<PageAppDiag>();

    addPage(Pages::ABOUT, appPageAbout);
    addPage(Pages::ERROR, appPageError);
    addPage(Pages::ABORT, appPageAbort);
    addPage(Pages::IDLE, appPageIdle);
    addPage(Pages::RUN, appPageRun);
    addPage(Pages::SETUP, appPageSetup);
    addPage(Pages::DIAG, appPageDiag);
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
        log("Page " + String(EnumHelpers::pagesHelper.ToString(pageEnum)) + " not found!", LogType::ERROR);
    }
}

std::shared_ptr<PageBase> DisplayManager::getPage(Pages pageEnum) {
    return pageMap[pageEnum];
}

void DisplayManager::refresh() {
    if (displayHandler != nullptr && currentPage != nullptr)
        currentPage->Draw(*displayHandler);
}
