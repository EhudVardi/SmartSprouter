#ifndef PAGEAPPERROR_H
#define PAGEAPPERROR_H

#include "GUI/PageAppBase.h"

class PageAppError : public PageAppBase {
protected:
    Label errorMessage;
    Label errorCode;

public:
    PageAppError() : errorMessage(2, SCREEN_HEIGHT  / 4, "", FontSize::Small),
                     errorCode(2, SCREEN_HEIGHT  / 4 + 12, "", FontSize::Small)  {
        SetTitle("Error");
        AddElement(&errorMessage);
        AddElement(&errorCode);
    }

    void SetError(String message, int code) {
        errorMessage.UpdateText("Message: " + message);
        errorCode.UpdateText("Code: " + String(code));
    }
};

#endif // PAGEAPPERROR_H
