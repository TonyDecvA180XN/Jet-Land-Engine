#include "InputHandler.h"



InputHandler::InputHandler(InputManager * input)
{
    inputManager_ = input;
    state_ = NULL;
}


InputHandler::~InputHandler()
{
}

VOID InputHandler::SetState(InputHandlerBaseState * state)
{
    state_ = state;
}

InputHandlerBaseState * InputHandler::GetState()
{
    return state_;
}

VOID InputHandler::Handle()
{
    state_->HandleInput(inputManager_);
}
