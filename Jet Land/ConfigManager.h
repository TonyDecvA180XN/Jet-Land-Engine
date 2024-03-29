#pragma once




#include "INIReader/INIReader.h"
#include "Configuration.h"

class ConfigManager
{
public:
    ConfigManager();
    ~ConfigManager();

    BOOL LoadConfig(LPSTR filename);
    VOID ApplyConfig(Configuration * config);

    VOID DeleteConfig();
private:
    INIReader * parser;
};

