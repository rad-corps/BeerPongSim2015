#include "GameOver.h"


GameOver::GameOver(int victor_)
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::GAME_OVER;
	backgroundImage = CreateSprite("./images/game_over.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	MoveSprite(backgroundImage, settings->GetInt("SCREEN_W") * 0.5f, settings->GetInt("SCREEN_H") * 0.5f);
	victor = string("PLAYER ") + to_string(victor_) + string(" CONGRATULATIONS");
}


GameOver::~GameOver()
{
}

void GameOver::Update()
{
}

void GameOver:: Draw()
{
	DrawString(victor.c_str(), settings->GetInt("GAME_OVER_TEXT_X"), settings->GetInt("GAME_OVER_TEXT_Y"));
	DrawSprite(backgroundImage);
}