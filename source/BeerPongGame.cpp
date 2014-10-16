#include "BeerPongGame.h"
#include "Menu.h"
#include "PlayGame.h"
#include "GameOver.h"
#include "AIE.h"
#include <string>

BeerPongGame::BeerPongGame()
{
	settings = FileSettings::Instance();
	//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
	Initialise( settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), false, "BEER PONG SIMULATOR 2015" );
	SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
	//AddFont( "./fonts/invaders.fnt" );
	//\Now lets create the sprite for our players cannon. That's right in space invaders we control a cannon
	//\So lets create that with an appropriate variable name and move it to a suitable location (say the middle of our screen)
	stateSelection = 0;
	currentState = new Menu();
}


BeerPongGame::~BeerPongGame()
{
}

void BeerPongGame::Run()
{
	do 
	{

		ClearScreen();

		//reload the settings file if 'R' is pressed
		if ( IsKeyDown(KEY_R) )
		{
			settings->ReloadIniFile();
		}

		if(stateSelection != currentState->stateSelection)
		{
			delete currentState;

			switch(stateSelection)
			{
			case MENU:
				currentState = new Menu();
				break;
			case PLAYING_GAME:
				currentState = new PlayGame();
				break;
			case GAME_OVER:
				currentState = new GameOver();
				break;
			default:
				break;
			}
		}	

		//Returns active current states - nice & tidy
		currentState->Update();
		currentState->Draw();

		if(IsKeyDown(KEY_1))
		{
			stateSelection = 1;
		}
		if(IsKeyDown(KEY_2))
		{
			stateSelection = 2;
		}
		if(IsKeyDown(KEY_ESCAPE))
		{
			stateSelection = 0;
		}



	} while ( FrameworkUpdate() == false );




}
