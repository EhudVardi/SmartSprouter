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

class DisplayDate {
private:
    int day, month, year;

    // Helper function to check if the year is a leap year
    bool IsLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Helper function to get the maximum days in a month
    int GetDaysInMonth(int m, int y) {
        switch (m) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;  // Months with 31 days
            case 4: case 6: case 9: case 11:
                return 30;  // Months with 30 days
            case 2:
                return IsLeapYear(y) ? 29 : 28;  // February handling leap year
            default:
                return 0;  // Invalid month
        }
    }

public:
    DisplayDate() : day(1), month(1), year(2000) {}
    DisplayDate(int d, int m, int y) : day(d), month(m), year(y) {}

    // Format as DD/MM/YYYY
    String ToString() const {
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", day, month, year);
        return String(buffer);
    }

    int GetDay() { return day; }
    int GetMonth() { return month; }
    int GetYear() { return year; }

    // SetDate function with validation
    bool SetDate(int d, int m, int y) {
        // Validate month
        if (m < 1 || m > 12) {
            return false;  // Invalid month
        }

        // Validate day based on the month and year
        int maxDays = GetDaysInMonth(m, y);
        if (d < 1 || d > maxDays) {
            return false;  // Invalid day for the given month
        }

        // If everything is valid, set the date
        day = d;
        month = m;
        year = y;
        return true;  // Success
    }
};

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

class DisplayTime {
private:
    int hour, minute, second;

public:
    DisplayTime() : hour(0), minute(0), second(0) {}
    DisplayTime(int h, int m, int s) : hour(h), minute(m), second(s) {}

    // Format time as HH:MM:SS
    String ToString() const {
        char buffer[9];
        snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, minute, second);
        return String(buffer);
    }

    // Format time as HH:MM
    String ToStringShort() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
        return String(buffer);
    }

    int getSecond() { return second; }
    int GetMinute() { return minute; }
    int GetHour() { return hour; }
    
    // SetTime function with validation
    bool SetTime(int h, int m, int s) {
        // Validate hour (0 to 23)
        if (h < 0 || h > 23) {
            return false;
        }
        // Validate minute (0 to 59)
        if (m < 0 || m > 59) {
            return false;
        }
        // Validate second (0 to 59)
        if (s < 0 || s > 59) {
            return false;
        }
        // If everything is valid, set the time
        hour = h;
        minute = m;
        second = s;
        return true;
    }
};


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