#include "Menu.h"

Menu::Menu()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::MENU;
	backgroundImage = CreateSprite("./images/beer_pong.jpg", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true );
	MoveSprite( backgroundImage, settings->GetInt("SCREEN_W") * 0.5f, settings->GetInt("SCREEN_H") * 0.5f );
}


Menu::~Menu()
{
}

void Menu::Update()
{
	cout << "MENU - MENU(ESCAPE) - PLAYGAME(1) - GAME OVER(2)" << endl;
}

void Menu::Draw()
{
	DrawSprite(backgroundImage);
}