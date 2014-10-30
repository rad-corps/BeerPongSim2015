#include "AIE.h"
#include "BeerPongGame.h"
#include "Menu.h"
#include "PlayGame.h"
#include "GameOver.h"
#include "Instructions.h"
#include <string>


void MyKeyEvent(int key_, void* caller_)
{
	BeerPongGame* bpg = (BeerPongGame*)caller_;
	bpg->KeyDown(key_);
}


//key up callback
void BeerPongGame::KeyDown(int key_)
{
	if(key_ == KEY_ENTER && currentState->stateSelection == GAME_STATES::MENU)
	{
		stateSelection = GAME_STATES::PLAYING_GAME;
	}
	if(key_ == KEY_ESCAPE && currentState->stateSelection != GAME_STATES::MENU)
	{
		stateSelection = GAME_STATES::MENU;
		BeerPongSound::StopAmbience();	
	}
	if ( key_ == KEY_ESCAPE && currentState->stateSelection == GAME_STATES::MENU)
	{
		stateSelection = GAME_STATES::SHUTTING_DOWN;
	}
	if(key_ == KEY_SPACE && currentState->stateSelection == GAME_STATES::MENU)
	{
		stateSelection = GAME_STATES::INSTRUCTIONS;
	}
}


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

	inputHelper.RegisterCallback(&MyKeyEvent, this);
	inputHelper.AddKey(KEY_ESCAPE);
	inputHelper.AddKey(KEY_SPACE);
	inputHelper.AddKey(KEY_ENTER);
}


BeerPongGame::~BeerPongGame()
{
}

void BeerPongGame::ShutDownGame()
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
				currentState = new PlayGame(this);
				break;
			case GAME_OVER:
				currentState = new GameOver(winner);
				break;
			case INSTRUCTIONS:
				currentState = new Instructions();
			case SHUTTING_DOWN:
				ShutDownGame();

			default:
				break;
			}
		}	

		//Returns active current states - nice & tidy
		currentState->Update();
		currentState->Draw();

		inputHelper.Update();

		if (stateSelection != SHUTTING_DOWN)
			FrameworkUpdate();

	} while ( stateSelection != SHUTTING_DOWN );
}

void BeerPongGame::GameOverEvent(int winner_)
{
	winner = winner_;
	stateSelection = GAME_STATES::GAME_OVER;
}