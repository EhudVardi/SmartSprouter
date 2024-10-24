#ifndef PAGEBASE_H
#define PAGEBASE_H

#include "GUI/Elements/GuiElement.h"
#include "GUI/Pages/Pages.h"
#include <vector>

class PageBase {
protected:
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

    virtual void InvalidatePage() {
        for (auto &element : elements) {
            element->Invalidate();
        }
    }

    virtual Pages getType() const = 0; // Using static casting with manual type checking to get a page by its sub type, by specifying its enum
};

#endif // PAGEBASE_H
