#include "PlayGame.h"
#include "CollisionCheck.h"


PlayGame::PlayGame()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::PLAYING_GAME;
	//backgroundImage = CreateSprite("./images/BeerPong.jpg", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	backgroundImage = CreateSprite("./images/bar-02.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
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

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Update(delta);
	}

	for(int i = 0; i < balls.size(); i++)
	{

		if ( balls[i].Active() ) 
		{
			balls[i].Update(delta);

			if ( CollisionCheck::CheckRectangleCollision(balls[i].GetCollider(), cup1.GetCollider()) )
			{
				cout << "Ball in CUP!!!" << endl;
			}
		}
	}

	cup1.Update(delta);

	

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

	cup1.Draw();

	
}

void PlayGame::ThrowBall(Vector2 pos_, float angle_, float velocity_)
{
	Ball ball = Ball(pos_, angle_, velocity_);
	balls.push_back(ball);
}