#pragma once
#include "GAMESTATE.h"
#include "FileSettings.h"
#include "StateObserver.h"
#include "InputHelper.h"
#include "BeerPongSound.h"

class BeerPongGame : StateObserver
{
public:
	BeerPongGame();
	~BeerPongGame();

	void Run();	
	virtual void GameOverEvent(int winner_);
	void KeyDown(int key_);

	

private:
	void ShutDownGame();
	GAMESTATE *currentState;
	FileSettings* settings;
	int stateSelection;
	InputHelper inputHelper;
	BeerPongSound* sound;
	int winner;
};