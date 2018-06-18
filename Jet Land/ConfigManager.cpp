#include "ConfigManager.h"



ConfigManager::ConfigManager()
{
    parser = NULL;
}


ConfigManager::~ConfigManager()
{
}

BOOL ConfigManager::LoadConfig(LPSTR filename)
{
    parser = new INIReader(filename);
    if (parser->ParseError() < 0) { return FALSE; }

    return TRUE;
}

VOID ConfigManager::ApplyConfig(Configuration * config)
{
    config->Screen.windowWidth = parser->GetInt("Screen", "iWindowWidth", 800);
    config->Screen.windowHeight = parser->GetInt("Screen", "iWindowHeight", 600);
    config->Screen.useForceResolution = parser->GetBool("Screen", "bUseForceResolution", false);
    config->Screen.enableFullscreen = parser->GetBool("Screen", "bEnableFullscreen", false);
    config->Screen.enableVSync = parser->GetBool("Screen", "bEnableVSync", true);

}

VOID ConfigManager::DeleteConfig()
{
    delete parser;
    parser = NULL;
}
