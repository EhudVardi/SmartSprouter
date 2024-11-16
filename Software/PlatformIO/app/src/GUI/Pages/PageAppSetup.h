#ifndef PAGEAPPSETUP_H
#define PAGEAPPSETUP_H

#include "PageAppBase.h"
#include "GUI/Elements/Composite/TypedNameRange.h"
#include "GUI/Elements/Composite/TypedNameValue.h"
#include "GUI/Elements/Simple/TypedLabel.h"
#include "Application/ApplicationConfig.h"

class PageAppSetup : public PageAppBase {
protected:
    NamedRangePercent humidityRangeSetup;
    NamedRangeTemperature temperatureRangeSetup;
    NamedValueTimeSpan durationSetup;
    CenteredLabel startButton;

public:
    PageAppSetup() : humidityRangeSetup(2, 12, def_humidityRangeSetupMin, def_humidityRangeSetupMax, "Humidity"),
                     temperatureRangeSetup(2, 24, def_temperatureRangeSetupMin, def_temperatureRangeSetupMax, "Temper'"),
                     durationSetup(2, 36, def_durationSetup, "Duration", FontSize::Small), 
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
    
    float GetSetupHumidityMin() { return humidityRangeSetup.GetMinValue(); }
    float GetSetupHumidityMax() { return humidityRangeSetup.GetMaxValue(); }
    float GetSetupTemperatureMin() { return temperatureRangeSetup.GetMinValue(); }
    float GetSetupTemperatureMax() { return temperatureRangeSetup.GetMaxValue(); } 
    AppTimeSpan GetDurationSetup() { return durationSetup.GetValue(); }

    void IncreaseHumidityMin() { humidityRangeSetup.IncreaseMin(); }
    void DecreaseHumidityMin() { humidityRangeSetup.DecreaseMin(); }
    void IncreaseHumidityMax() { humidityRangeSetup.IncreaseMax(); }
    void DecreaseHumidityMax() { humidityRangeSetup.DecreaseMax(); }

    void IncreaseTemperatureMin() { temperatureRangeSetup.IncreaseMin(); }
    void DecreaseTemperatureMin() { temperatureRangeSetup.DecreaseMin(); }
    void IncreaseTemperatureMax() { temperatureRangeSetup.IncreaseMax(); }
    void DecreaseTemperatureMax() { temperatureRangeSetup.DecreaseMax(); }
    
    void IncreaseDurationDays() { 
        durationSetup.addDays(1); 
    }
    void DecreaseDurationDays() { 
        durationSetup.addDays(-1);
    }
};

#endif // PAGEAPPSETUP_H
