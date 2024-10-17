#ifndef NAMEDVALUEINT_H
#define NAMEDVALUEINT_H

#include "GUI/NamedValue.h"

class NamedValueInt : public NamedValue<int> {
protected:
    String FormatValue(int value) const override {
        return String(value); // general int formatting
    }

public:
    NamedValueInt(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<int>(xPos, yPos, name, size) {}

    void SetValue(int newValue) {
        NamedValue<int>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEINT_H


#ifndef NAMEDVALUEFLOAT_H
#define NAMEDVALUEFLOAT_H

#include "GUI/NamedValue.h"

class NamedValueFloat : public NamedValue<float> {
protected:
    String FormatValue(float value) const override {
        return String(value, 2); // general float formatting - 2 decimal places for float values
    }

public:
    NamedValueFloat(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {}

    void SetValue(float newValue) {
        NamedValue<float>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEFLOAT_H


#ifndef NAMEDVALUEPERCENT_H
#define NAMEDVALUEPERCENT_H

class NamedValuePercent : public NamedValue<float> {
protected:
    String FormatValue(float value) const override {
        // Create a result string with a fixed width for the numeric value
        String result;
        result.reserve(15); // Reserve enough space for formatting and the "%"
        
        // Format the float with 1 decimal place and append the '%' directly
        char buffer[15]; // Buffer to hold the formatted number with percentage
        snprintf(buffer, sizeof(buffer), "%6.1f %%", value); // 6 total width, 1 decimal place
        
        result += buffer; // Append formatted number with percent
        return result; // Return the final result
    }

public:
    NamedValuePercent(int xPos, int yPos, const String &name, FontSize size = FontSize::Small)
        : NamedValue<float>(xPos, yPos, name, size) {}

    void SetValue(float newValue) {
        NamedValue<float>::SetValue(newValue);
    }
};

#endif // NAMEDVALUEPERCENT_H

