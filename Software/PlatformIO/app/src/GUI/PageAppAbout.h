#ifndef PAGEAPPABOUT_H
#define PAGEAPPABOUT_H

#include "GUI/PageAppBase.h"
#include "GUI/Image.h"
#include "GUI/AppLogoImage.h"
#include "ApplicationProperties.h"

class PageAppAbout : public PageAppBase {
protected:
    Image LogoImage;
    Label appName;
    Label appVersion;

public:
    PageAppAbout() : LogoImage(2, (SCREEN_HEIGHT - abstractsproutingseedimage_height) / 2, 
                               abstractsproutingseedimage_bitmap, 
                               abstractsproutingseedimage_width, abstractsproutingseedimage_height),
                     appName(abstractsproutingseedimage_width + 4, SCREEN_HEIGHT  / 4,
                             appNameText, FontSize::Small),
                     appVersion(abstractsproutingseedimage_width + 4, SCREEN_HEIGHT  / 4 + 12,
                                "Version " + appVersionText, FontSize::Small) {
        SetTitle("About");
        AddElement(&LogoImage);
        AddElement(&appName);
        AddElement(&appVersion);
    }
    
    Pages getType() const override {
        return Pages::About;
    }
};

#endif // PAGEAPPABOUT_H
