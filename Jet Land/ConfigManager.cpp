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
	if (!parser) { return FALSE; }
	if (parser->ParseError())
	{
		return FALSE;
	}

	return TRUE;
}

VOID ConfigManager::ApplyConfig(Configuration * config)
{
	config->Screen.windowWidth = parser->GetInt("Screen", "iWindowWidth", 0);
	config->Screen.windowHeight = parser->GetInt("Screen", "iWindowHeight", 0);
	config->Screen.useForceResolution = parser->GetBool("Screen", "bUseForceResolution", false);
	config->Screen.enableBorderlessWindow = parser->GetBool("Screen", "bEnableBorderlessWindow", true);
	config->Screen.enableFullscreen = parser->GetBool("Screen", "bEnableFullscreen", false);
	config->Screen.hideCursor = parser->GetBool("Screen", "bHideCursor", FALSE);
	config->Screen.enableVSync = parser->GetBool("Screen", "bEnableVSync", true);
	config->Screen.multiSampleAACount = parser->GetInt("Screen", "iMSAAcount", 1);

}

VOID ConfigManager::DeleteConfig()
{
	delete parser;
	parser = NULL;
}
