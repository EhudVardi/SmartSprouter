#ifndef PAGEAPPABOUT_H
#define PAGEAPPABOUT_H

#include "GUI/PageAppBase.h"
#include "GUI/Image.h"
#include "GUI/AppLogoImage.h"

class PageAppAbout : public PageAppBase {
protected:
    Image LogoImage;

public:
    PageAppAbout() : LogoImage( (SCREEN_WIDTH - abstractsproutingseedimage_width) / 2, 
                                (SCREEN_HEIGHT - abstractsproutingseedimage_height) / 2, 
                                abstractsproutingseedimage_bitmap, 
                                abstractsproutingseedimage_width, 
                                abstractsproutingseedimage_height ) {
        AddElement(&LogoImage);
        SetTitle(">About<");
    }
};

#endif // PAGEAPPABOUT_H
