#ifndef PAGEAPPIDLE_H
#define PAGEAPPIDLE_H

#include "GUI/PageAppBase.h"
#include "GUI/TypedNameValue.h"

class PageAppIdle : public PageAppBase {
protected:
    NamedValuePercent humidityGauge;
    NamedValuePercent temperatureGauge;
    NamedValueDate currentDate;
    NamedValueTime currentTime;

public:
    PageAppIdle() : humidityGauge(2, 12, "Humidity", FontSize::Small),
                    temperatureGauge(2, 24, "Temper'", FontSize::Small), 
                    currentDate(2, 36, "Date", FontSize::Small),
                    currentTime(2, 48, "Time", FontSize::Small) {
        SetTitle("Idle");
        AddElement(&humidityGauge);
        AddElement(&temperatureGauge);
        AddElement(&currentDate);
        AddElement(&currentTime);
    }

    bool SetHumidity(float humidityPercent) {
        if (humidityPercent >= 0.0 &&  humidityPercent <= 100.0) {
            humidityGauge.SetValue(humidityPercent);
            return true;
        }
        else {
            return false;
        }
    }

    bool SetTemperature(float temperature) {
        if (temperature >= 0.0 &&  temperature <= 100.0) {
            temperatureGauge.SetValue(temperature);
            return true;
        }
        else {
            return false;
        }
    }

    bool SetDate(int day, int month, int year) {
        return currentDate.SetDate(day, month, year);
    }

    bool SetTime(int second, int minute, int hour) {
        return currentTime.SetTime(second, minute, hour);
    }
};

#endif // PAGEAPPIDLE_H
