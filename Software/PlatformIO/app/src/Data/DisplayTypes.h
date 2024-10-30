#include <Arduino.h>

#ifndef DISPLAYTYPES_H
#define DISPLAYTYPES_H

#define DAY_IN_SECONDS 86400
#define HOUR_IN_SECONDS 3600
#define MINUTE_IN_SECONDS 60

class DisplayDuration {
private:
    unsigned long seconds;

public:
    DisplayDuration() : seconds(0) {}

    DisplayDuration(int days, int hrs, int mins, int secs) {
        seconds = days * DAY_IN_SECONDS + hrs * HOUR_IN_SECONDS + mins * MINUTE_IN_SECONDS + secs;
    }

    // Format duration as D:HH:MM:SS
    String ToString() const {
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d:%02d", GetDays(), GetHours(), GetMinutes(), GetSeconds());
        return String(buffer);
    }
    String toString() const { return ToStringShort(); }

    // Format duration as D:HH:MM
    String ToStringShort() const {
        char buffer[8];
        snprintf(buffer, sizeof(buffer), "%01d:%02d:%02d", GetDays(), GetHours(), GetMinutes());
        return String(buffer);
    }

    int GetSeconds() const { return seconds % MINUTE_IN_SECONDS; }
    int GetMinutes() const { return (seconds % HOUR_IN_SECONDS) / MINUTE_IN_SECONDS; }
    int GetHours() const { return (seconds % DAY_IN_SECONDS) / HOUR_IN_SECONDS; }
    int GetDays() const { return seconds / DAY_IN_SECONDS; }

    // Add positive or negative seconds, preventing underflow
    void AddSeconds(int secs) {
        if (secs < 0 && static_cast<unsigned long>(-secs) > seconds) {
            seconds = 0;  // Prevent underflow
        } else {
            seconds += secs;
        }
    }
    void AddMinutes(int mins) {
        AddSeconds(mins * MINUTE_IN_SECONDS);  // Reuse AddSeconds with conversion
    }
    void AddHours(int hrs) {
        AddSeconds(hrs * HOUR_IN_SECONDS);  // Reuse AddSeconds with conversion
    }
    void AddDays(int days) {
        AddSeconds(days * DAY_IN_SECONDS);  // Reuse AddSeconds with conversion
    }

    void TickDown() {
        if (seconds > 0) {
            seconds--;
        }
    }

    unsigned long GetTotalSeconds() const { return seconds; }
};

#endif // DISPLAYTYPES_H
