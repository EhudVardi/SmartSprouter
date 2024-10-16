#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <Adafruit_SSD1306.h>

class GuiElement {
protected:
    int x, y;         // Position
    bool invalidated; // Invalidated flag

public:
    GuiElement(int xPos, int yPos) : x(xPos), y(yPos), invalidated(true) {}

    virtual void Draw(Adafruit_SSD1306 &display) = 0; // Pure virtual function

    void Invalidate() {
        invalidated = true; // Mark as needing redraw
    }

    bool IsInvalidated() const {
        return invalidated;
    }

    virtual ~GuiElement() = default; // Virtual destructor for inheritance
};

#endif // GUIELEMENT_H
