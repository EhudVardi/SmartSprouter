#ifndef NAMEDVALUEINT_H
#define NAMEDVALUEINT_H

#include "GUI/NamedValue.h"

class NamedValueInt : public NamedValue<int> {
protected:
    String FormatValue(int value) const override {
        return String(value); // general int formatting
    }

public:
    NamedValueInt(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<int>(xPos, yPos, name, size) {}

    void SetValue(int newValue) {
        NamedValue<int>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEINT_H


#ifndef NAMEDVALUEFLOAT_H
#define NAMEDVALUEFLOAT_H

#include "GUI/NamedValue.h"

class NamedValueFloat : public NamedValue<float> {
protected:
    String FormatValue(float value) const override {
        return String(value, 2); // general float formatting - 2 decimal places for float values
    }

public:
    NamedValueFloat(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {}

    void SetValue(float newValue) {
        NamedValue<float>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEFLOAT_H


#ifndef NAMEDVALUEPERCENT_H
#define NAMEDVALUEPERCENT_H

#include "GUI/NamedValue.h"

class NamedValuePercent : public NamedValueFloat {
protected:
    String FormatValue(float value) const override {
        char buffer[8]; // Adjust size as necessary
        snprintf(buffer, sizeof(buffer), "%3.1f%%", value);
        return String(buffer);
    }
public:
    NamedValuePercent(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {}
};

#endif // NAMEDVALUEPERCENT_H


#ifndef NAMEDVALUETEMPERATURE_H
#define NAMEDVALUETEMPERATURE_H

#include "GUI/NamedValue.h"

class NamedValueTemperature : public NamedValueFloat {
protected:
    String FormatValue(float value) const override {
        char buffer[7]; // Adjust size as necessary
        snprintf(buffer, sizeof(buffer), "%3.1fC", value);
        return String(buffer);
    }
public:
    NamedValueTemperature(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValueFloat(xPos, yPos, name, size) {}
};

#endif // NAMEDVALUETEMPERATURE_H


#ifndef NAMEDVALUEDATE_H
#define NAMEDVALUEDATE_H

#include "GUI/NamedValue.h"
#include "GUI/DisplayTypes.h"

class NamedValueDate : public NamedValue<DisplayDate> {
protected:
    // Format the Date object
    String FormatValue(DisplayDate value) const override {
        return value.ToString();  // Convert the Date object to a formatted string
    }

public:
    NamedValueDate(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDate>(xPos, yPos, name, size) {}

    void SetValue(const DisplayDate &newDate) {
        NamedValue<DisplayDate>::SetValue(newDate);
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
protected:
    String FormatValue(DisplayTime value) const override {
        return value.ToString();
    }

public:
    NamedValueTime(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayTime>(xPos, yPos, name, size) {}

    void SetValue(const DisplayTime &newTime) {
        NamedValue<DisplayTime>::SetValue(newTime);
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
protected:
    String FormatValue(DisplayDuration value) const override {
        return value.ToString();
    }

public:
    NamedValueDuration(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<DisplayDuration>(xPos, yPos, name, size) {}

    void SetValue(const DisplayDuration &newDuration) {
        NamedValue<DisplayDuration>::SetValue(newDuration);
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