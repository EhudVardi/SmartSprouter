#ifndef CENTERED_LABEL_H
#define CENTERED_LABEL_H

#include "Label.h"

class CenteredLabel : public Label {
private:
    bool positionCalculated; // Flag to track if the position has been calculated
    int centeredX;           // Cached x position for centering

public:
    CenteredLabel(int yPos, const String &initialText, FontSize size = FontSize::Large)
        : Label(0, yPos, initialText, size), positionCalculated(false), centeredX(0) {
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        Adafruit_SSD1306 &display = displayHandler.GetDisplayObject(); // Get the display object

        if (!positionCalculated) {
            // Calculate text bounds to determine width only once
            int16_t x1, y1;
            uint16_t textWidth, textHeight;

            // Set font size
            display.setTextSize(static_cast<uint8_t>(fontSize));

            // Get text bounds
            display.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);

            // Center the text
            centeredX = (display.width() - textWidth) / 2; // Centering based on actual display width

            // Directly set the inherited x position
            x = centeredX; // Set the x position
            positionCalculated = true; // Mark the position as calculated
        }

        // Call the base class Draw method to render the text
        Label::Draw(displayHandler);
    }

    // Optionally, provide a method to reset the position if needed
    void ResetPosition() {
        positionCalculated = false; // Allows recalculation on the next Draw
    }
};

#endif // CENTERED_LABEL_H
