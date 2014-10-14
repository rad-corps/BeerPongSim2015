#pragma once

//A little helper for using CIniFile

#include <map>
#include <string>

//singleton settings class
class FileSettings
{

public:
	~FileSettings(void);
	static FileSettings* Instance();
	float GetFloat(std::string key_);
	int GetInt(std::string key_);
	std::string GetString(std::string key_);
	void ReloadIniFile();
	
private:
	FileSettings(void);
	
	static FileSettings* instance;

	std::map<std::string, std::string> settingsMap;
};

