#ifndef NAMEDVALUEINT_H
#define NAMEDVALUEINT_H

#include "GUI/NamedValue.h"

class NamedValueInt : public NamedValue<int> {
public:
    NamedValueInt(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<int>(xPos, yPos, name, size) {
        // Set a custom formatter for general int display
        valueLabel.SetFormatter([](int value) {
            return String(value);
        });
    }
    NamedValueInt(int xPos, int yPos, int initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValueInt(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEINT_H


#ifndef NAMEDVALUEFLOAT_H
#define NAMEDVALUEFLOAT_H

#include "GUI/NamedValue.h"

class NamedValueFloat : public NamedValue<float> {
public:
    NamedValueFloat(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            return String(value);
        });
    }
    NamedValueFloat(int xPos, int yPos, float initialValue, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        SetValue(initialValue);
    }
};

#endif // NAMEDVALUEFLOAT_H


#ifndef NAMEDVALUEPERCENT_H
#define NAMEDVALUEPERCENT_H

#include "GUI/NamedValue.h"

class NamedValuePercent : public NamedValueFloat {
public:
    NamedValuePercent(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            char buffer[8];
            snprintf(buffer, sizeof(buffer), "%3.1f%%", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUEPERCENT_H


#ifndef NAMEDVALUETEMPERATURE_H
#define NAMEDVALUETEMPERATURE_H

#include "GUI/NamedValue.h"

class NamedValueTemperature : public NamedValueFloat {
public:
    NamedValueTemperature(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), "%3.1fC", value);
            return String(buffer);
        });
    }
};

#endif // NAMEDVALUETEMPERATURE_H


#ifndef NAMEDVALUEDATE_H
#define NAMEDVALUEDATE_H

#include "GUI/NamedValue.h"
#include "GUI/DisplayTypes.h"

class NamedValueDate : public NamedValue<DisplayDate> {
public:
    NamedValueDate(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDate>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayDate value) {
            return value.ToString();
        });
    }

    bool SetDate(int d, int m, int y) {
        DisplayDate newDate;
        if (!newDate.SetDate(d, m, y))
            return false;
        SetValue(newDate);
        return true;
    }
};

#endif // NAMEDVALUEDATE_H

#ifndef NAMEDVALUETIME_H
#define NAMEDVALUETIME_H

#include "GUI/NamedValue.h"
#include "GUI/DisplayTypes.h"

class NamedValueTime : public NamedValue<DisplayTime> {
public:
    NamedValueTime(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayTime>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayTime value) {
            return value.ToString();
        });
    }

    bool SetTime(int s, int m, int h) {
        DisplayTime newTime;
        if (!newTime.SetTime(s, m, h))
            return false;
        SetValue(newTime);
        return true;
    }
};

#endif // NAMEDVALUETIME_H

#ifndef NAMEDVALUEDURATION_H
#define NAMEDVALUEDURATION_H

#include "GUI/NamedValue.h"
#include "GUI/DisplayTypes.h"

class NamedValueDuration : public NamedValue<DisplayDuration> {
public:
    NamedValueDuration(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDuration>(xPos, yPos, name, size) {
        valueLabel.SetFormatter([](DisplayDuration value) {
            return value.ToString();
        });
    }

    void AddSeconds(int secs) { DisplayDuration newDuration = GetValue(); newDuration.AddSeconds(secs); SetValue(newDuration); }
    void AddMinutes(int mins) { DisplayDuration newDuration = GetValue(); newDuration.AddMinutes(mins); SetValue(newDuration); }
    void AddHours(int hrs) { DisplayDuration newDuration = GetValue(); newDuration.AddHours(hrs); SetValue(newDuration); }
    void AddDays(int days) { DisplayDuration newDuration = GetValue(); newDuration.AddDays(days); SetValue(newDuration); }

    void TickDown() {
        DisplayDuration newDuration = GetValue(); newDuration.TickDown(); SetValue(newDuration);
    }
};

#endif // NAMEDVALUEDURATION_H