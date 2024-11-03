#include <Arduino.h>
#include <RTClib.h>

#ifndef DISPLAYTYPES_H
#define DISPLAYTYPES_H

#define DAY_IN_SECONDS 86400
#define HOUR_IN_SECONDS 3600
#define MINUTE_IN_SECONDS 60

class DisplayTimeSpan : public TimeSpan {
public:
    DisplayTimeSpan() : TimeSpan(0) {}
    DisplayTimeSpan(int totalSeconds) : TimeSpan(totalSeconds) {}
    DisplayTimeSpan(int days, int hrs, int mins, int secs) : TimeSpan(days, hrs, mins, secs) {}

    // Format duration as D:HH:MM:SS
    String ToString() const {
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d:%02d", days(), hours(), minutes(), seconds());
        return String(buffer);
    }
    // Format duration as D:HH:MM
    String ToStringShort() const {
        char buffer[8];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d", days(), hours(), minutes());
        return String(buffer);
    }
    String toString() const { return ToStringShort(); }
    
    void AddSeconds(int secs) { _seconds = max(0, _seconds + secs); } // Add positive or negative seconds, preventing underflow
    void AddMinutes(int mins) { AddSeconds(mins * MINUTE_IN_SECONDS); }
    void AddHours(int hrs) { AddSeconds(hrs * HOUR_IN_SECONDS); }
    void AddDays(int days) { AddSeconds(days * DAY_IN_SECONDS); }

    void TickDown() {
        if (_seconds > 0) {
            _seconds--;
        }
    }
    
    bool operator==(const DisplayTimeSpan& other) const {
        return totalseconds() == other.totalseconds();
    }
    bool operator!=(const DisplayTimeSpan& other) const {
        return !(*this == other);
    }
    DisplayTimeSpan operator+(const DisplayTimeSpan &right) const {
        return DisplayTimeSpan(_seconds + right._seconds);
    }
    DisplayTimeSpan operator-(const DisplayTimeSpan &right) const {
        return DisplayTimeSpan(_seconds - right._seconds);
    }
};

class DisplayDateTime : public DateTime {
public:
    DisplayDateTime() : DateTime() {}
    DisplayDateTime(int year, int month, int day, int hour, int minute, int second) : DateTime(year, month, day, hour, minute, second) {}
    DisplayDateTime(const DateTime& dt) : DateTime(dt) {}
    
    String ToArduinoString() const {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", 
                 year(), month(), day(), hour(), minute(), second());
        return String(buffer);
    }
    
    bool operator==(const DisplayDateTime& other) const {
        return unixtime() == other.unixtime();
    }
    bool operator!=(const DisplayDateTime& other) const {
        return !(*this == other);
    }
    DisplayDateTime operator-(const DisplayTimeSpan &span) const {
        return DisplayDateTime(unixtime() - span.totalseconds());
    }
    DisplayTimeSpan operator-(const DisplayDateTime &right) const {
        return DisplayTimeSpan(unixtime() - right.unixtime());
    }
};

#endif // DISPLAYTYPES_H
