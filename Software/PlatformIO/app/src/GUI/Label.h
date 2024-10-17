#ifndef LABEL_H
#define LABEL_H

#include "GUI/GuiElement.h"
#include "GUI/FontSize.h"
#include <Arduino.h>

class Label : public GuiElement {
private:
    String text;
    FontSize fontSize;
    bool inverted; // New member to determine if label is inverted

public:
    Label(int xPos, int yPos, const String &initialText, FontSize size = FontSize::Small)
        : GuiElement(xPos, yPos), text(initialText), fontSize(size), inverted(false) {}

    void UpdateText(const String &newText) {
        if (newText != text) {
            text = newText;
            Invalidate(); // Mark as needing redraw
        }
    }

    void SetFontSize(FontSize size) {
        fontSize = size;
        Invalidate(); // Change in size requires redraw
    }

    void SetInverted(bool state) {
        inverted = state;
        Invalidate(); // Inversion state change requires redraw
    }

    bool IsInverted() const {
        return inverted;
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        int16_t x1, y1;
        uint16_t w, h;

        Adafruit_SSD1306& display = displayHandler.GetDisplayObject();

        // Set font size based on enum
        display.setTextSize(static_cast<uint8_t>(fontSize));

        // Get text bounds for clearing
        display.getTextBounds(text, x, y, &x1, &y1, &w, &h);

        // Clear the area
        display.fillRect(x1, y1, w, h, inverted ? SSD1306_WHITE : SSD1306_BLACK);
        
        // Set text color
        display.setTextColor(inverted ? SSD1306_BLACK : SSD1306_WHITE);

        // Set cursor and print text
        display.setCursor(x, y);
        display.print(text);

        // Update the display
        display.display();

        // Clear invalidation flag
        invalidated = false;
    }
};

#endif // LABEL_H
