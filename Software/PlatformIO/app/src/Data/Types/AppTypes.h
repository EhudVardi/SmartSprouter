#include <Arduino.h>
#include <RTClib.h>

#ifndef APPTYPES_H
#define APPTYPES_H

#define DAY_IN_SECONDS 86400
#define HOUR_IN_SECONDS 3600
#define MINUTE_IN_SECONDS 60

class AppTimeSpan : public TimeSpan {
public:
    AppTimeSpan() : TimeSpan(0) {}
    AppTimeSpan(int totalSeconds) : TimeSpan(totalSeconds) {}
    AppTimeSpan(int days, int hrs, int mins, int secs) : TimeSpan(days, hrs, mins, secs) {}

    // Format duration as D:HH:MM:SS
    String ToString() const {
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d:%02d", days(), hours(), minutes(), seconds());
        return String(buffer);
    }
    // Format duration as D:HH:MM
    String toStringShort() const {
        char buffer[8];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d", days(), hours(), minutes());
        return String(buffer);
    }
    String toString() const { return toStringShort(); }
    
    void addSeconds(int secs) { _seconds = max(0, _seconds + secs); } // Add positive or negative seconds, preventing underflow
    void addMinutes(int mins) { addSeconds(mins * MINUTE_IN_SECONDS); }
    void addHours(int hrs) { addSeconds(hrs * HOUR_IN_SECONDS); }
    void addDays(int days) { addSeconds(days * DAY_IN_SECONDS); }

    void tickDown() {
        if (_seconds > 0) {
            _seconds--;
        }
    }
    
    bool operator==(const AppTimeSpan& other) const {
        return totalseconds() == other.totalseconds();
    }
    bool operator!=(const AppTimeSpan& other) const {
        return !(*this == other);
    }
    AppTimeSpan operator+(const AppTimeSpan &right) const {
        return AppTimeSpan(_seconds + right._seconds);
    }
    AppTimeSpan operator-(const AppTimeSpan &right) const {
        return AppTimeSpan(_seconds - right._seconds);
    }
};

class AppDateTime : public DateTime {
public:
    AppDateTime() : DateTime() {}
    AppDateTime(int year, int month, int day, int hour, int minute, int second) : DateTime(year, month, day, hour, minute, second) {}
    AppDateTime(const DateTime& dt) : DateTime(dt) {}
    
    String ToString() const {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", 
                 year(), month(), day(), hour(), minute(), second());
        return String(buffer);
    }
    
    bool operator==(const AppDateTime& other) const {
        return unixtime() == other.unixtime();
    }
    bool operator!=(const AppDateTime& other) const {
        return !(*this == other);
    }
    AppDateTime operator-(const AppTimeSpan &span) const {
        return AppDateTime(unixtime() - span.totalseconds());
    }
    AppTimeSpan operator-(const AppDateTime &right) const {
        return AppTimeSpan(unixtime() - right.unixtime());
    }
};

#endif // APPTYPES_H
