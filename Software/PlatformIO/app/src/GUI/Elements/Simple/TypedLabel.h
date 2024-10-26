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
        
    void UpdateText(const String &newText) {
        if (newText != value) {
            value = newText;
            Invalidate(); // Mark as needing redraw
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


#ifndef DATE_LABEL_H
#define DATE_LABEL_H

class DateLabel : public Label<DisplayDate> {
public:
    DateLabel(int xPos, int yPos, DisplayDate initialDate, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialDate;
            if (!formatter) {
                SetFormatter([](DisplayDate value) { return value.toString(); });
            }
        }
        
    void SetDate(const DisplayDate &newDate) {
        value = newDate;
        Invalidate();
    }
};

#endif // DATE_LABEL_H


#ifndef TIME_LABEL_H
#define TIME_LABEL_H

class TimeLabel : public Label<DisplayTime> {
public:
    TimeLabel(int xPos, int yPos, DisplayTime initialTime, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialTime;
            if (!formatter) {
                SetFormatter([](DisplayTime value) { return value.toString(); });
            }
        }
        
    void SetTime(const DisplayTime &newTime) {
        value = newTime;
        Invalidate();
    }

    void Tick() {
        value.Tick();
        Invalidate();
    }
};

#endif // TIME_LABEL_H