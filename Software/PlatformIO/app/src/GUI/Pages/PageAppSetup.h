#ifndef PAGEAPPSETUP_H
#define PAGEAPPSETUP_H

#include "GUI/Pages/PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameRange.h"
#include "GUI/Elements/Composite/TypedNameValue.h"
#include "GUI/Elements/Simple/TypedLabel.h"

class PageAppSetup : public PageAppBase {
protected:
    NamedRangePercent humidityRangeSetup;
    NamedRangeTemperature temperatureRangeSetup;
    NamedValueTimeSpan durationSetup;
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
    
    Pages getType() const override {
        return Pages::Setup;
    }

    void SetHumidityRangeSelectionMode(NamedRangeEditState newEditState) {
        humidityRangeSetup.SetEditState(newEditState);
    }
    void SetTemperatureRangeSelectionMode(NamedRangeEditState newEditState) {
        temperatureRangeSetup.SetEditState(newEditState);
    }
    void SetDurationSelectionMode(NamedValueEditState newEditState) {
        durationSetup.SetEditState(newEditState);
    }
    void SetStartSelectionMode(bool selected) {
        startButton.SetInverted(selected);
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
        durationSetup.AddDays(-1);
    }
};

#endif // PAGEAPPSETUP_H
