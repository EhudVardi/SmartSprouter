#ifndef HW_BUTTON_HANDLER_H
#define HW_BUTTON_HANDLER_H

#include <vector>
#include "HWButton.h"

// HWButtonHandler class to manage multiple buttons
class HWButtonHandler {
private:
  std::vector<HWButton> buttons;

public:
  HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers_onPress, const std::vector<std::function<void()>>& handlers_onRelease);
  void updateButtons();
  std::vector<HWButton>& getButtons();
};

#endif