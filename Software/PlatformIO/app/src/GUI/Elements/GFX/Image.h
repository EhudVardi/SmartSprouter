#ifndef IMAGE_H
#define IMAGE_H

#include "GUI/Elements/GUIElement.h"
#include "HardwareAbstraction/LcdDisplayHandler.h"

class Image : public GuiElement {
private:
    const uint8_t* imageData; // Pointer to the image data (black/white bitmap)
    int imageWidth; // Image width in pixels
    int imageHeight; // Image height in pixels

public:
    // Constructor: Position is given, image size is inferred from the provided data
    Image(int xPos, int yPos, const uint8_t* imageData, int imageWidth, int imageHeight)
        : GuiElement(xPos, yPos), imageData(imageData), imageWidth(imageWidth), imageHeight(imageHeight) {}

    void Draw(LcdDisplayHandler &displayHandler) override {
        if (!IsInvalidated()) return;
        
        Adafruit_SSD1306& display = displayHandler.GetDisplayObject();
        display.drawBitmap(x, y, imageData, imageWidth, imageHeight, SSD1306_WHITE);
        invalidated = false;
        display.display();
    }

    void SetImageData(const uint8_t* newImageData, int newWidth, int newHeight) {
        imageData = newImageData;
        imageWidth = newWidth;
        imageHeight = newHeight;
        Invalidate();
    }

    void SetPosition(int xPos, int yPos) {
        x = xPos;
        y = yPos;
        Invalidate();
    }
};

#endif // IMAGE_H
