#pragma once
#include "GAMESTATE.h"
#include "FileSettings.h"

class GameOver : public GAMESTATE
{
public:
	GameOver();
	~GameOver();

	void Update();
	void Draw();

private:
	FileSettings* settings;
};

