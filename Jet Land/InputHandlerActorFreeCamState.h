#pragma once

#include "InputHandlerBaseState.h"
#include "ActorFreeCam.h"

class InputHandlerActorFreeCamState :
    public InputHandlerBaseState
{
public:
    InputHandlerActorFreeCamState(ActorFreeCam * actor);
    ~InputHandlerActorFreeCamState();

    VOID AttachActor(ActorFreeCam * actor);
    VOID HandleInput(InputManager * input) override;

private:
    ActorFreeCam * actor_;
};

