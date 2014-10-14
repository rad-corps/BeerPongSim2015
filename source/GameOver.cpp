#include "GameOver.h"


GameOver::GameOver()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::GAME_OVER;
	backgroundImage = CreateSprite("./images/bar-girl.jpg", 512, 512, true);
	MoveSprite(backgroundImage, settings->GetInt("SCREEN_W") * 0.5f, settings->GetInt("SCREEN_H") * 0.5f);
}


GameOver::~GameOver()
{
}

void GameOver::Update()
{
	cout << "GAME OVER - MENU(ESCAPE) - PLAYGAME(1) - GAME OVER(2)" << endl;
}

void GameOver:: Draw()
{
	DrawSprite(backgroundImage);
}