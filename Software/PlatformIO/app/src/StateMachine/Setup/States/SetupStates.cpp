#include "StateMachine/Setup/States/SetupStates.h"
#include "SystemContext/SystemContext.h"
#include <iostream>

void HR_S::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void HR_S::exit(SystemContext* context) { }
void HR_S::update(SystemContext* context) { }
void HR_S::handleInput(SystemContext* context, InputEvent event) { }

void HR_E_MIN::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void HR_E_MIN::exit(SystemContext* context) { }
void HR_E_MIN::update(SystemContext* context) { }
void HR_E_MIN::handleInput(SystemContext* context, InputEvent event) { }

void HR_E_MAX::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void HR_E_MAX::exit(SystemContext* context) { }
void HR_E_MAX::update(SystemContext* context) { }
void HR_E_MAX::handleInput(SystemContext* context, InputEvent event) { }

void TR_S::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void TR_S::exit(SystemContext* context) { }
void TR_S::update(SystemContext* context) { }
void TR_S::handleInput(SystemContext* context, InputEvent event) { }

void TR_E_MIN::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void TR_E_MIN::exit(SystemContext* context) { }
void TR_E_MIN::update(SystemContext* context) { }
void TR_E_MIN::handleInput(SystemContext* context, InputEvent event) { }

void TR_E_MAX::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void TR_E_MAX::exit(SystemContext* context) { }
void TR_E_MAX::update(SystemContext* context) { }
void TR_E_MAX::handleInput(SystemContext* context, InputEvent event) { }

void D_S::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void D_S::exit(SystemContext* context) { }
void D_S::update(SystemContext* context) { }
void D_S::handleInput(SystemContext* context, InputEvent event) { }

void D_E::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void D_E::exit(SystemContext* context) { }
void D_E::update(SystemContext* context) { }
void D_E::handleInput(SystemContext* context, InputEvent event) { }

void S_S::enter(SystemContext* context) { 
    SetupState::enter(context);
}
void S_S::exit(SystemContext* context) { }
void S_S::update(SystemContext* context) { }
void S_S::handleInput(SystemContext* context, InputEvent event) { }

