#ifndef PAGEAPPERROR_H
#define PAGEAPPERROR_H

#include "PageAppBase.h"
#include "StateMachine/App/AppErrorsEnum.h"

class PageAppError : public PageAppBase {
protected:
    TextLabel errorEnum;
    TextLabel errorParams;

public:
    PageAppError() : errorEnum(2, SCREEN_HEIGHT  / 4, "", FontSize::Small),
                     errorParams(2, SCREEN_HEIGHT  / 4 + 12, "", FontSize::Small)  {
        SetTitle("Error");
        AddElement(&errorEnum);
        AddElement(&errorParams);
    }
    
    Pages getType() const override {
        return Pages::Error;
    }

    void SetError(AppErrors& error, const String& errParams) {
        errorEnum.SetValue(EnumHelpers::AppErrorsHelper.ToString(error));
        errorParams.SetValue(errParams);
    }
};

#endif // PAGEAPPERROR_H
