#include <Arduino.h>

#ifndef DISPLAYTYPES_H
#define DISPLAYTYPES_H

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
    bool SetTime(int s, int m, int h) {
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

#endif // DISPLAYTYPES_H
