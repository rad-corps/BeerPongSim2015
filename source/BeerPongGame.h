#pragma once
#include "GAMESTATE.h"
#include "FileSettings.h"

class BeerPongGame
{
public:
	BeerPongGame();
	~BeerPongGame();

	void Run();

private:
	GAMESTATE *currentState;
	FileSettings* settings;
	int stateSelection;
};