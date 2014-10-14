#pragma once
#include "GAMESTATE.h"
#include "FileSettings.h"

class Menu : public GAMESTATE
{
public:
	Menu();
	~Menu();

	void Update();
	void Draw();

private:
	FileSettings* settings;
};

