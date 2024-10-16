#ifndef PAGE_H
#define PAGE_H

#include "GUI/GuiElement.h"
#include <vector>

class Page {
private:
    std::vector<GuiElement*> elements;

public:
    void AddElement(GuiElement *element) {
        elements.push_back(element);
    }

    void Draw(Adafruit_SSD1306 &display) {
        for (auto &element : elements) {
            if (element->IsInvalidated()) {
                element->Draw(display);
            }
        }
    }
};

#endif // PAGE_H
