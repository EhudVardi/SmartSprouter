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

    void Draw(LcdDisplayHandler &displayHandler) {
        for (auto &element : elements) {
            if (element->IsInvalidated()) {
                element->Draw(displayHandler);
            }
        }
    }
};

#endif // PAGE_H
