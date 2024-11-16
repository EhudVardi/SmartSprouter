#ifndef PAGEAPPRUN_H
#define PAGEAPPRUN_H

#include "PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameValue.h"

class PageAppRun : public PageAppBase {
protected:
    NamedValuePercent humidityGauge;
    NamedValueTemperature temperatureGauge;
    NamedValueTimeSpan durationGauge;

public:
    PageAppRun() :
        humidityGauge(2, 12, "Humidity", FontSize::Small),
        temperatureGauge(2, 24, "Temper'", FontSize::Small),
        durationGauge(2, 36, "Duration", FontSize::Small) {
        SetTitle("RUNNING");
        AddElement(&humidityGauge);
        AddElement(&temperatureGauge);
        AddElement(&durationGauge);
    }

    Pages getType() const override {
        return Pages::RUN;
    }

    bool SetHumidity(float humidityPercent) {
        if (humidityPercent >= 0.0 && humidityPercent <= 100.0) {
            humidityGauge.SetValue(humidityPercent);
            return true;
        }
        else {
            return false;
        }
    }

    bool SetTemperature(float temperature) {
        if (temperature >= 0.0 && temperature <= 100.0) {
            temperatureGauge.SetValue(temperature);
            return true;
        }
        else {
            return false;
        }
    }

    void SetDuration(AppTimeSpan remainingTime) {
        durationGauge.SetValue(remainingTime);
    }

    void TickDurationDown() {
        durationGauge.tickDown();
    }
};

#endif // PAGEAPPRUN_H
