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
};

class NamedRangePercent : public NamedRange<float> {
public:
    NamedRangePercent(int xPos, int yPos, const String &name)
        : NamedRange<float>(xPos, yPos, name) {
        // Set a custom formatter for percentage display
        valueRange.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), "%3.0f%% ", value);
            return String(buffer);
        });
    }
};

class NamedRangeTemperature : public NamedRange<float> {
public:
    NamedRangeTemperature(int xPos, int yPos, const String &name)
        : NamedRange<float>(xPos, yPos, name) {
        // Set a custom formatter for temperature display with "C" appended
        valueRange.SetFormatter([](float value) {
            char buffer[7];
            snprintf(buffer, sizeof(buffer), " %3.1fC", value);
            return String(buffer);
        });
    }
};

#endif // TYPED_NAMED_RANGE_H
