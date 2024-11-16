#include "Label.h"

#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

class TextLabel : public Label<String> {
public:
    TextLabel(int xPos, int yPos, String initialText, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialText;
            // Default simple string conversion formatter if not provided
            if (!formatter) {
                SetFormatter([](String value) { return String(value); });
            }
        }
};

#endif // TEXT_LABEL_H


#ifndef CENTERED_LABEL_H
#define CENTERED_LABEL_H

class CenteredLabel : public TextLabel {
private:
    bool positionCalculated; // Flag to track if the position has been calculated
    int centeredX; // Cached x position for centering

public:
    CenteredLabel(int yPos, const String &initialText, FontSize size = FontSize::Large)
        : TextLabel(0, yPos, initialText, size), positionCalculated(false), centeredX(0) {
    }

    virtual void Draw(LcdDisplayHandler &displayHandler) override {
        Adafruit_SSD1306 &display = displayHandler.GetDisplayObject();

        if (!positionCalculated) {
            
            int16_t x1, y1;
            uint16_t textWidth, textHeight;
            display.getTextBounds(value, 0, 0, &x1, &y1, &textWidth, &textHeight);
            display.setTextSize(static_cast<uint8_t>(fontSize));
            centeredX = (display.width() - textWidth) / 2; // Centering the text based on actual display width
            x = centeredX; // Directly Set the inherited x position
            positionCalculated = true; // Mark the position as calculated
        }

        // Call the base class Draw method to render the text
        Label::Draw(displayHandler);
    }

    // reset calculation flag to force re-calculation on next draw
    void ResetPosition() {
        positionCalculated = false;
    }
};

#endif // CENTERED_LABEL_H


#ifndef FLOAT_LABEL_H
#define FLOAT_LABEL_H

class FloatLabel : public Label<float> {
public:
    FloatLabel(int xPos, int yPos, float initialvalue, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialvalue;
            SetFormatter([](float value) { return String(value); });
        }
};

#endif // FLOAT_LABEL_H


#ifndef HUMIDITY_LABEL_H
#define HUMIDITY_LABEL_H

class PercentLabel : public FloatLabel {
public:
    PercentLabel(int xPos, int yPos, float initialvalue, FontSize size = FontSize::Small)
        : FloatLabel(xPos, yPos, initialvalue, size) {
            SetFormatter([](float value) {
                char buffer[7];
                snprintf(buffer, sizeof(buffer), "%3.1f%%", value);
                return String(buffer);
            });
        }
};

#endif // HUMIDITY_LABEL_H


#ifndef TEMPERATURE_LABEL_H
#define TEMPERATURE_LABEL_H

class TemperatureLabel : public FloatLabel {
public:
    TemperatureLabel(int xPos, int yPos, float initialvalue, FontSize size = FontSize::Small)
        : FloatLabel(xPos, yPos, initialvalue, size) {
            SetFormatter([](float value) {
                char buffer[7];
                snprintf(buffer, sizeof(buffer), "%3.1fC", value);
                return String(buffer);
            });
        }
};

#endif // TEMPERATURE_LABEL_H


#ifndef DISPLAYDATETIME_LABEL_H
#define DISPLAYDATETIME_LABEL_H

class DisplayDateTimeLabel : public Label<AppDateTime> {
public:
    DisplayDateTimeLabel(int xPos, int yPos, AppDateTime initialDateTime, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialDateTime;
        }
        
    void SetDateTime(const AppDateTime &newDate) {
        value = newDate;
        Invalidate();
    }
};

#endif // DISPLAYDATETIME_LABEL_H
