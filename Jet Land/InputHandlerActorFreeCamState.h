#pragma once

#include "InputHandlerBaseState.h"
#include "Actor.h"

class InputHandlerActorFreeCamState :
    public InputHandlerBaseState
{
public:
    InputHandlerActorFreeCamState(Actor * actor);
    ~InputHandlerActorFreeCamState();

    VOID AttachActor(Actor * actor);
    VOID HandleInput(InputManager * input) override;

private:
    Actor * actor_;
};

