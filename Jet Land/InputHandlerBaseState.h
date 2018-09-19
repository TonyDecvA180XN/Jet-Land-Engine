#pragma once



#include "InputManager.h"

class InputHandlerBaseState
{
public:
    InputHandlerBaseState();
    virtual ~InputHandlerBaseState();

    virtual VOID HandleInput(InputManager * input);
};

