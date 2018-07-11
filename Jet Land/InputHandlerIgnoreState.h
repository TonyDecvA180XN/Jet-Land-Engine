#pragma once

#include "InputHandlerBaseState.h"

class InputHandlerIgnoreState :
    public InputHandlerBaseState
{
public:
    InputHandlerIgnoreState();
    ~InputHandlerIgnoreState();

    VOID HandleInput(InputManager * input) override;
};

