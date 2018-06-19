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
    if (parser->ParseError()) 
    {
        std::wstring error;
        LPTSTR wfilename = new WCHAR[200];
        auto a = new size_t(0);
        mbstowcs_s(a, wfilename, strlen(filename) + 1, LPCSTR(filename), 200);
        if (parser->ParseError() < 0)
        {
            error += L"Error parsing configuration file.\n";
            error += L"Cannot open file \"";
            error += wfilename;
            error += L"\".\n\n\n";
            CrashManager::CrashLog(L"crash.txt", error);
        } else
        {
            error += L"Error parsing configuration file.\n";
            error += L"Invalid configuration file \"";
            error += wfilename;
            error += L"\"(line ";
            error += std::to_wstring(parser->ParseError());
            error += L").\n\n\n";
            CrashManager::CrashLog(L"crash.txt", error);
        }
        return FALSE;
    }

    return TRUE;
}

VOID ConfigManager::ApplyConfig(Configuration * config)
{
    config->Screen.windowWidth = parser->GetInt("Screen", "iWindowWidth", 800);
    config->Screen.windowHeight = parser->GetInt("Screen", "iWindowHeight", 600);
    config->Screen.useForceResolution = parser->GetBool("Screen", "bUseForceResolution", false);
    config->Screen.enableBorderlessWindow = parser->GetBool("Screen", "bEnableBorderlessWindow", true);
    config->Screen.enableFullscreen = parser->GetBool("Screen", "bEnableFullscreen", false);
    config->Screen.enableVSync = parser->GetBool("Screen", "bEnableVSync", true);

}

VOID ConfigManager::DeleteConfig()
{
    delete parser;
    parser = NULL;
}
