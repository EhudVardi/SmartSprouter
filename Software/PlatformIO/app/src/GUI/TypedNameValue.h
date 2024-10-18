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

class Date {
public:
    int day, month, year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    
    // Format as DD/MM/YYYY
    String ToString() const {
        char buffer[11]; 
        snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", day, month, year);
        return String(buffer);
    }
};

class NamedValueDate : public NamedValue<Date> {
protected:
    // Format the Date object
    String FormatValue(Date value) const override {
        return value.ToString();  // Convert the Date object to a formatted string
    }

public:
    NamedValueDate(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<Date>(xPos, yPos, name, size) {}

    void SetValue(const Date &newDate) {
        NamedValue<Date>::SetValue(newDate);
    }
};

#endif // NAMEDVALUEDATE_H

#ifndef NAMEDVALUETIME_H
#define NAMEDVALUETIME_H

class Time {
public:
    int hour, minute, second;

    Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

    // Format time as HH:MM:SS
    String ToString() const {
        char buffer[9]; 
        snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, minute, second);
        return String(buffer);
    }
};

class NamedValueTime : public NamedValue<Time> {
protected:
    String FormatValue(Time value) const override {
        return value.ToString();
    }

public:
    NamedValueTime(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<Time>(xPos, yPos, name, size) {}

    void SetValue(const Time &newTime) {
        NamedValue<Time>::SetValue(newTime);
    }
};


#endif // NAMEDVALUETIME_H