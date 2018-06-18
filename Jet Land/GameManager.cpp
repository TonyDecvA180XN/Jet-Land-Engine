#include "GameManager.h"



GameManager::GameManager()
{
    windowsManager_ = new WindowsManager;
    isExit_ = FALSE;
}


GameManager::~GameManager()
{
}

BOOL GameManager::Initialize(HINSTANCE h_instance)
{
    windowsManager_->CreateGameWindow(
        h_instance,
        1024,
        768,
        FALSE,
        FALSE
    );

    return TRUE;
}

VOID GameManager::Terminate()
{
    if (windowsManager_)
    {
        windowsManager_->DestroyGameWindow();
        delete windowsManager_;
        windowsManager_ = NULL;
    }
}

VOID GameManager::Execute()
{
    while (!isExit_)
    {
        BOOL result;

        result = windowsManager_->Update();
        if (!result) {isExit_ = TRUE;}
        Sleep(10);
    }
}
