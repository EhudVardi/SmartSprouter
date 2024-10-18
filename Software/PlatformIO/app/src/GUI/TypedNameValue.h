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

class NamedValuePercent : public NamedValue<float> {
protected:
    String FormatValue(float value) const override {
        char buffer[10]; // Adjust size as necessary
        snprintf(buffer, sizeof(buffer), "%6.1f %%", value);
        return String(buffer);
    }

public:
    NamedValuePercent(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {}

    void SetValue(float newValue) {
        NamedValue<float>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEPERCENT_H


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