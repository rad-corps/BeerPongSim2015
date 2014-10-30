#pragma once
#include "GAMESTATE.h"
#include "FileSettings.h"
#include <string>

class GameOver : public GAMESTATE
{
public:
	GameOver(int victor_);
	~GameOver();

	void Update();
	void Draw();

private:
	FileSettings* settings;
	string victor;
};

