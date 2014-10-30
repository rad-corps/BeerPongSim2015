#include "Menu.h"

Menu::Menu()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::MENU;
	backgroundImage = CreateSprite("./images/beer_pong_startv1.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true );
	MoveSprite( backgroundImage, settings->GetInt("SCREEN_W") * 0.5f, settings->GetInt("SCREEN_H") * 0.5f );
	cout << "MENU - MENU(ESCAPE) - PLAYGAME(1) - GAME OVER(2)" << endl;
}


Menu::~Menu()
{
}

void Menu::Update()
{
}

void Menu::Draw()
{
	DrawSprite(backgroundImage);
}