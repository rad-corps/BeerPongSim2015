#pragma once
#include <iostream>
#include "AIE.h"

using namespace std;

enum GAME_STATES
{
	MENU,				//Includes instruction
	PLAYING_GAME,		//Game Running
	GAME_OVER,				//Thanks for playing
};

class GAMESTATE
{
public:
	GAMESTATE();
	~GAMESTATE();

	virtual void Update()=0;
	virtual void Draw()=0;

	int stateSelection;

protected:
	unsigned int backgroundImage;

};

