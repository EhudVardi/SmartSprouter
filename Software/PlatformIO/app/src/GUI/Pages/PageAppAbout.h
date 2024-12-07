#ifndef PAGEAPPABOUT_H
#define PAGEAPPABOUT_H

#include "PageAppBase.h"
#include "GUI/Elements/GFX/Image.h"
#include "GUI/Bitmaps/AppLogoImage.h"
#include "Application/ApplicationProperties.h"

class PageAppAbout : public PageAppBase {
protected:
    Image LogoImage;
    TextLabel appName;
    TextLabel appVersion;

public:
    PageAppAbout() :
        LogoImage(2, (SCREEN_HEIGHT - abstractsproutingseedimage_height) / 2,
            abstractsproutingseedimage_bitmap, abstractsproutingseedimage_width, abstractsproutingseedimage_height),
        appName(abstractsproutingseedimage_width + 4, SCREEN_HEIGHT / 4, APP_NAME_TEXT, FontSize::Small),
        appVersion(abstractsproutingseedimage_width + 4, SCREEN_HEIGHT / 4 + 12, "Version " + APP_VERSION_TEXT, FontSize::Small) {
        SetTitle("About");
        AddElement(&LogoImage);
        AddElement(&appName);
        AddElement(&appVersion);
    }

    Pages getType() const override {
        return Pages::ABOUT;
    }
};

#endif // PAGEAPPABOUT_H
