#ifndef RANGE_H
#define RANGE_H

#include <Arduino.h>
#include <functional>
#include "GUI/Elements/GuiElement.h"
#include "GUI/Elements/FontSize.h"

template <typename T>
class Range : public GuiElement {
private:
    T minValue;               // Minimum value
    T maxValue;               // Maximum value
    bool minInverted;         // Inversion state for min value
    bool maxInverted;         // Inversion state for max value
    std::function<String(T)> formatter; // Function to format the value

public:
    Range(int xPos, int yPos, T initialMinValue, T initialMaxValue, std::function<String(T)> customFormatter = nullptr)
        : Range(xPos, yPos, customFormatter) {
            SetMinValue(initialMinValue);
            SetMaxValue(initialMaxValue);
        }

    Range(int xPos, int yPos, std::function<String(T)> customFormatter = nullptr)
        : GuiElement(xPos, yPos),
          minInverted(false),
          maxInverted(false),
          formatter(customFormatter) {
        // Default formatter if not provided
        if (!formatter) {
            SetFormatter([](T value) { return String(value); }); // Default to simple string conversion
        }
    }

    // Set a custom formatter later
    void SetFormatter(std::function<String(T)> customFormatter) {
        formatter = customFormatter;
    }

    // Getters
    T GetMinValue() const { return minValue; }
    T GetMaxValue() const { return maxValue; }

    // Setters with invalidation
    void SetMinValue(T newMinValue) {
        if (newMinValue != minValue) {
            minValue = newMinValue;
            Invalidate();
        }
    }

    void SetMaxValue(T newMaxValue) {
        if (newMaxValue != maxValue) {
            maxValue = newMaxValue;
            Invalidate();
        }
    }

    // Set inversion states
    void SetMinInverted(bool state) {
        if (state != minInverted) {
            minInverted = state;
            Invalidate();
        }
    }

    void SetMaxInverted(bool state) {
        if (state != maxInverted) {
            maxInverted = state;
            Invalidate();
        }
    }

    // Draw with formatted values
    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;

        Adafruit_SSD1306& display = displayHandler.GetDisplayObject();
        int16_t x1, y1;
        uint16_t w, h;

        // Use the formatter to format the min and max values
        String minStr = formatter(minValue);
        String maxStr = formatter(maxValue);

        // Drawing logic (same as before, using formatted strings)
        display.setTextSize(1);
        display.getTextBounds(minStr, x, y, &x1, &y1, &w, &h);
        display.fillRect(x, y, w, h, minInverted ? SSD1306_WHITE : SSD1306_BLACK);
        display.setTextColor(minInverted ? SSD1306_BLACK : SSD1306_WHITE);
        display.setCursor(x, y);
        display.print(minStr);

        display.getTextBounds(maxStr, x + w + 2, y, &x1, &y1, &w, &h);
        display.fillRect(x + w + 2, y, w, h, maxInverted ? SSD1306_WHITE : SSD1306_BLACK);
        display.setTextColor(maxInverted ? SSD1306_BLACK : SSD1306_WHITE);
        display.setCursor(x + w + 2, y);
        display.print(maxStr);

        display.display();
        invalidated = false;
    }
};

#endif // RANGE_H
