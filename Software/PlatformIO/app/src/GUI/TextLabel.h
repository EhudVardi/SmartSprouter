#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "GUI/Label.h"

class TextLabel : public Label<String> {
public:
    TextLabel(int xPos, int yPos, String initialText, FontSize size = FontSize::Small)
        : Label(xPos, yPos, size) {
            value = initialText;
            // Default formatter if not provided
            if (!formatter) {
                SetFormatter([](String value) { return String(value); }); // Default to simple string conversion
            }
        }
        
    void UpdateText(const String &newText) {
        if (newText != value) {
            value = newText;
            Invalidate(); // Mark as needing redraw
        }
    }
};

#endif // TEXT_LABEL_H
