#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "HardwareAbstraction/LcdDisplayHandler.h"
#include "HardwareAbstraction/LcdDisplayProperties.h"

class GuiElement {
protected:
    int x, y; // Position
    bool invalidated; // Invalidated flag

public:
    GuiElement(int xPos, int yPos) : x(xPos), y(yPos), invalidated(true) {}

    virtual void Draw(LcdDisplayHandler &displayHandler) = 0; // Pure virtual function

    virtual void Invalidate() {
        invalidated = true; // Mark as needing redraw
    }

    virtual bool IsInvalidated() const {
        return invalidated;
    }

    virtual ~GuiElement() = default; // Virtual destructor for inheritance
};

#endif // GUIELEMENT_H
