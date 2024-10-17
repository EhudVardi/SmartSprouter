#ifndef PAGEAPPABOUT_H
#define PAGEAPPABOUT_H

#include "GUI/PageAppBase.h"
#include "GUI/Image.h"
#include "GUI/AppLogoImage.h"

class PageAppAbout : public PageAppBase {
protected:
    Image LogoImage;

public:
    PageAppAbout() : LogoImage((SCREEN_WIDTH - smileyBitmapWidth) / 2, (SCREEN_HEIGHT - smileyBitmapHeight) / 2, smileyBitmap, smileyBitmapWidth, smileyBitmapHeight ) {
        AddElement(&LogoImage);
        SetTitle(">About<");
    }
};

#endif // PAGEAPPABOUT_H
