#ifndef PAGEAPPRUN_H
#define PAGEAPPRUN_H

#include "GUI/PageAppBase.h"
#include "GUI/TypedNameValue.h"

class PageAppRun : public PageAppBase {
protected:
    NamedValuePercent humidityGauge;
    NamedValuePercent temperatureGauge;
    NamedValueDuration durationGauge;

public:
    PageAppRun() : humidityGauge(2, 12, "Humidity", FontSize::Small),
                   temperatureGauge(2, 24, "Temper'", FontSize::Small),
                   durationGauge(2, 36, "Duration", FontSize::Small) {
        SetTitle("Running");
        AddElement(&humidityGauge);
        AddElement(&temperatureGauge);
        AddElement(&durationGauge);
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

    void SetDuration(int days, int hrs, int mins, int secs) {
        durationGauge.AddDays(days);
        durationGauge.AddHours(hrs);
        durationGauge.AddMinutes(mins);
        durationGauge.AddSeconds(secs);
    }

    void TickDurationDown() {
        durationGauge.TickDown();
    }
};

#endif // PAGEAPPRUN_H
