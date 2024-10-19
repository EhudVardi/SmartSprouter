#ifndef TYPED_NAMED_RANGE_H
#define TYPED_NAMED_RANGE_H

#include "GUI/NamedRange.h"
#include "GUI/Range.h"

class NamedRangeInt : public NamedRange<int> {
public:
    NamedRangeInt(int xPos, int yPos, const String &name)
        : NamedRange<int>(xPos, yPos, name) {
        // Set a custom formatter for general int display
        valueRange.SetFormatter([](int value) {
            return String(value);
        });
    }
    NamedRangeInt(int xPos, int yPos, int minValue, int maxValue, const String &name)
        : NamedRangeInt(xPos, yPos, name) {
            SetMinValue(minValue);
            SetMaxValue(maxValue);
    }
    
    void IncreaseMin() { int minValue = GetMinValue(); int maxValue = GetMaxValue(); if (maxValue > minValue) SetMinValue(minValue + 1); }
    void DecreaseMin() { int minValue = GetMinValue(); if (minValue > 0) SetMinValue(minValue - 1); }

    void IncreaseMax() { int maxValue = GetMaxValue(); if (maxValue < 100) SetMaxValue(maxValue + 1); }
    void DecreaseMax() { int minValue = GetMinValue(); int maxValue = GetMaxValue(); if (maxValue > minValue) SetMaxValue(maxValue - 1); }

};

class NamedRangeFloat : public NamedRange<float> {
public:
    NamedRangeFloat(int xPos, int yPos, const String &name)
        : NamedRange<float>(xPos, yPos, name) {
        // Set a custom formatter for general float display
        valueRange.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), "%.2f", value);
            return String(buffer);
        });
    }
    NamedRangeFloat(int xPos, int yPos, float minValue, float maxValue, const String &name)
        : NamedRangeFloat(xPos, yPos, name) {
            SetMinValue(minValue);
            SetMaxValue(maxValue);
    }
    
    void IncreaseMin() { float minValue = GetMinValue(); float maxValue = GetMaxValue(); if (maxValue > minValue) SetMinValue(minValue + 1); }
    void DecreaseMin() { float minValue = GetMinValue(); if (minValue > 0) SetMinValue(minValue - 1); }

    void IncreaseMax() { float maxValue = GetMaxValue(); if (maxValue < 100) SetMaxValue(maxValue + 1); }
    void DecreaseMax() { float minValue = GetMinValue(); float maxValue = GetMaxValue(); if (maxValue > minValue) SetMaxValue(maxValue - 1); }
    
};

class NamedRangePercent : public NamedRangeFloat {
public:
    NamedRangePercent(int xPos, int yPos, float minValue, float maxValue, const String &name)
        : NamedRangeFloat(xPos, yPos, minValue, maxValue, name) {
        // Set a custom formatter for percentage display
        valueRange.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), "%3.0f%% ", value);
            return String(buffer);
        });
    }
};

class NamedRangeTemperature : public NamedRangeFloat {
public:
    NamedRangeTemperature(int xPos, int yPos, float minValue, float maxValue, const String &name)
        : NamedRangeFloat(xPos, yPos, minValue, maxValue, name) {
        // Set a custom formatter for temperature display with "C" appended
        valueRange.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), " %3.0fC", value);
            return String(buffer);
        });
    }
};

#endif // TYPED_NAMED_RANGE_H
