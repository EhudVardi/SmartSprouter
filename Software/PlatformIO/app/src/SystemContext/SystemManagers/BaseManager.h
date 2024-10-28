#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include "Application/ApplicationConfig.h"

class BaseManager {
public:
    virtual bool initialize() = 0;
};

#endif // BASE_MANAGER_H