#ifndef PAGEAPPSETUP_H
#define PAGEAPPSETUP_H

#include "GUI/PageAppBase.h"
#include "GUI/TypedNameRange.h"
#include "GUI/TypedNameValue.h"
#include "GUI/CenteredLabel.h"

class PageAppSetup : public PageAppBase {
protected:
    NamedRangePercent humidityRangeSetup;
    NamedRangeTemperature temperatureRangeSetup;
    NamedValueDuration durationSetup;
    CenteredLabel startButton;

public:
    PageAppSetup() : humidityRangeSetup(2, 12, 0, 100, "Humidity"),
                     temperatureRangeSetup(2, 24, 0, 100, "Temper'"),
                     durationSetup(2, 36, "Duration", FontSize::Small), 
                     startButton(48, "Start", FontSize::Medium)  {
        SetTitle("Setup");
        AddElement(&humidityRangeSetup);
        AddElement(&temperatureRangeSetup);
        AddElement(&durationSetup);
        AddElement(&startButton);
    }

    void IncreaseHumidityMin() { humidityRangeSetup.IncreaseMin(); }
    void DecreaseHumidityMin() { humidityRangeSetup.DecreaseMin(); }

    void IncreaseHumidityMax() { humidityRangeSetup.IncreaseMax(); }
    void DecreaseHumidityMax() { humidityRangeSetup.DecreaseMax(); }


    void IncreaseTemperatureMin() { temperatureRangeSetup.IncreaseMin(); }
    void DecreaseTemperatureMin() { temperatureRangeSetup.DecreaseMin(); }

    void IncreaseTemperatureMax() { temperatureRangeSetup.IncreaseMax(); }
    void DecreaseTemperatureMax() { temperatureRangeSetup.DecreaseMax(); }
    

    void IncreaseDurationDays() { 
        durationSetup.AddDays(1); 
    }
    void DecreaseDurationDays() { 
        int currDays = durationSetup.GetValue().GetDays();
        if (currDays > 1)
            durationSetup.GetValue().AddDays(-1);
    }
};

#endif // PAGEAPPSETUP_H
