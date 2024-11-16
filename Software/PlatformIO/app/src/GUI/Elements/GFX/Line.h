#ifndef LINE_H
#define LINE_H

#include "GUI/Elements/GuiElement.h"

class Line : public GuiElement {
private:
    int length;
    bool horizontal;  // True -> horizontal, false -> vertical

public:
    // Constructor for a general line with specified position, length, and orientation
    Line(int xPos, int yPos, int length, bool horizontal = true)
        : GuiElement(xPos, yPos), length(length), horizontal(horizontal) {}

    // Constructor for a full-screen-width horizontal line
    Line(int yPos) 
        : GuiElement(0, yPos), length(SCREEN_WIDTH), horizontal(true) {}

    // Constructor for a full-screen-height vertical line
    Line(bool /*dummy*/, int xPos) 
        : GuiElement(xPos, 0), length(SCREEN_HEIGHT), horizontal(false) {}

    void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;
        
        Adafruit_SSD1306& display = displayHandler.GetDisplayObject();
        if (horizontal) {
            display.drawLine(x, y, x + length, y, SSD1306_WHITE);
        } else {
            display.drawLine(x, y, x, y + length, SSD1306_WHITE);
        }
        invalidated = false;
        display.display();
    }

    void SetLength(int newLength) {
        length = newLength;
        Invalidate();
    }

    void SetOrientation(bool isHorizontal) {
        horizontal = isHorizontal;
        Invalidate();
    }

    void SetPosition(int xPos, int yPos) {
        x = xPos;
        y = yPos;
        Invalidate();
    }
};

#endif // LINE_H
