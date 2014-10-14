#include "FileSettings.h"
#include "IniFile.h"
#include <vector>
//#include "Consts.h"
//#include <Windows.h>

FileSettings* FileSettings::instance = nullptr;

FileSettings* 
FileSettings::Instance()
{
    // Lazy initialize.
    if (instance == nullptr) 
		instance = new FileSettings();
    
	return instance;
}

float FileSettings::GetFloat(std::string key_)
{
	return std::stof(settingsMap[key_]);
}

int FileSettings::GetInt(std::string key_)
{
	return std::stoi(settingsMap[key_]);
}

std::string FileSettings::GetString(std::string key_)
{
	return settingsMap[key_];
}

void FileSettings::ReloadIniFile()
{
	settingsMap.clear();

	const string INI_FILE_PATH = "./BeerPong2015Settings.ini";
	const string INI_SECTION = "game_globals";

	vector<CIniFile::Record> records = CIniFile::GetSection(INI_SECTION, INI_FILE_PATH);
	
	//put records in a map
	for (int i = 0; i < records.size(); ++i )
	{
		settingsMap[records[i].Key] = records[i].Value;
	}
}

FileSettings::FileSettings(void)
{
	//grab all variables from file, and toss them in a map.
	ReloadIniFile();
}


FileSettings::~FileSettings(void)
{
}
