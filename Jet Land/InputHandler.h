#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "InputManager.h"
#include "InputHandlerBaseState.h"

class InputHandler
{
public:
    InputHandler(InputManager * input);
    ~InputHandler();

    VOID SetState(InputHandlerBaseState * state);
    InputHandlerBaseState * GetState();
    VOID Handle();

private:
    InputManager * inputManager_;
    InputHandlerBaseState * state_;
};

