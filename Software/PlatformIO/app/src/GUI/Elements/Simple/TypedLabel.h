#include "GUI/Elements/Simple/Label.h"
#include "Data/ToString.h"

#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

class TextLabel : public Label<String> {
public:
    TextLabel(int xPos, int yPos, String initialText, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialText;
            // Default formatter if not provided
            if (!formatter) {
                SetFormatter([](String value) { return String(value); }); // Default to simple string conversion
            }
        }
};

#endif // TEXT_LABEL_H


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
                char buffer[8];
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


#ifndef DATETIME_LABEL_H
#define DATETIME_LABEL_H

class DateTimeLabel : public Label<DateTime> {
public:
    DateTimeLabel(int xPos, int yPos, DateTime initialDateTime, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialDateTime;
        }
        
    void SetDateTime(const DateTime &newDate) {
        value = newDate;
        Invalidate();
    }
};

#endif // DATETIME_LABEL_H
