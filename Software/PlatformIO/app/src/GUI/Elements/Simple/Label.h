#ifndef LABEL_H
#define LABEL_H

#include <Arduino.h>
#include <functional>
#include "GUI/Elements/GuiElement.h"
#include "GUI/Elements/FontSize.h"
#include "Data/Types/ToString.h"

template <typename T>
class Label : public GuiElement {
protected:
    T value;
    FontSize fontSize;
    bool inverted; // white-on-black / black-on-white
    std::function<String(T)> formatter;

public:
    Label(int xPos, int yPos, T initialValue, FontSize size = FontSize::Small, std::function<String(T)> customFormatter = nullptr)
        : Label(xPos, yPos, size, customFormatter) {
            value = initialValue;
        }
    
    Label(int xPos, int yPos, FontSize size = FontSize::Small, std::function<String(T)> customFormatter = nullptr)
        : GuiElement(xPos, yPos), 
        fontSize(size), 
        inverted(false),
        formatter(customFormatter) {
        // Default simple string conversion formatter if not provided
        if (!formatter) {
            SetFormatter([](T value) { return toString(value); });
        }
    }
    
    void SetFormatter(std::function<String(T)> customFormatter) {
        formatter = customFormatter;
    }

    T GetValue() const { return value; }
    
    void SetValue(T newValue) {
        value = newValue;
        Invalidate();
    }

    void SetFontSize(FontSize size) {
        fontSize = size;
        Invalidate();
    }

    void SetInverted(bool state) {
        if (state != inverted) {
            inverted = state;
            Invalidate();
        }
    }

    bool IsInverted() const {
        return inverted;
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        Adafruit_SSD1306& display = displayHandler.GetDisplayObject();
        int16_t x1, y1;
        uint16_t w, h;

        String valueStr = formatter(value);

        display.setTextSize(static_cast<uint8_t>(fontSize)); // Set font size based on enum
        display.getTextBounds(valueStr, x, y, &x1, &y1, &w, &h); // Get text bounds for clearing
        display.fillRect(x1, y1, w, h, inverted ? SSD1306_WHITE : SSD1306_BLACK); // Clear the area
        display.setTextColor(inverted ? SSD1306_BLACK : SSD1306_WHITE);
        display.setCursor(x, y);
        display.print(valueStr);

        display.display();
        invalidated = false;
    }
};

#endif // LABEL_H
