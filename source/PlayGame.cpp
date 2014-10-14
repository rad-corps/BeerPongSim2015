#include "PlayGame.h"


PlayGame::PlayGame()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::PLAYING_GAME;
	backgroundImage = CreateSprite("./images/BeerPong.jpg", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	MoveSprite(backgroundImage, settings->GetInt("SCREEN_W")*0.5f, settings->GetInt("SCREEN_H")*0.5f);
	
	PlayerHand p1 = PlayerHand(this);
	players.push_back(p1);
}


PlayGame::~PlayGame()
{
}

void PlayGame::Update()
{
	float delta = GetDeltaTime();
	//cout << "PLAYING GAME -  MENU(ESCAPE) - PLAYGAME(1) - GAME OVER(2)" << endl;

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Update(delta);
	}

	for(int i = 0; i < balls.size(); i++)
	{
		balls[i].Update(delta);
	}

	//[TO DO]  Iterate through ball vector & delete !active balls
}

void PlayGame::Draw()
{
	DrawSprite(backgroundImage);

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Draw();
	}

	for(int i = 0; i < balls.size(); i++)
	{
		balls[i].Draw();
	}
}

void PlayGame::ThrowBall(Vector2 pos_, float angle_, float velocity_)
{
	ball = new Ball(pos_, angle_, velocity_);
	balls.push_back(*ball);

	std::cout << "Throw Ball - pos: " << pos_ << " \tangle: " << angle_ << "\tvelocity: " << velocity_ << endl;
}