#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"
#include "InputManager.h"

class InputHandlerBaseState
{
public:
    InputHandlerBaseState();
    virtual ~InputHandlerBaseState();

    virtual VOID HandleInput(InputManager * input);
};

