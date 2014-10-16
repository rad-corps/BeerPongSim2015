#include "PlayGame.h"
#include "CollisionCheck.h"
#include "PlayerControls.h"


PlayGame::PlayGame()
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::PLAYING_GAME;
	//backgroundImage = CreateSprite("./images/BeerPong.jpg", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	backgroundImage = CreateSprite("./images/bar-02.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	MoveSprite(backgroundImage, settings->GetInt("SCREEN_W")*0.5f, settings->GetInt("SCREEN_H")*0.5f);
	
	PlayerControls p1Controls;
	p1Controls.up = KEY_W;
	p1Controls.down = KEY_S;
	p1Controls.anticlockwise = KEY_A;
	p1Controls.clockwise = KEY_D;
	p1Controls.throwBall = KEY_LEFT_CONTROL;

	PlayerControls p2Controls;
	p2Controls.up = KEY_UP;
	p2Controls.down = KEY_DOWN;
	p2Controls.anticlockwise = KEY_LEFT;
	p2Controls.clockwise = KEY_RIGHT;
	p2Controls.throwBall = KEY_RIGHT_CONTROL;

	PlayerInitialisers p1Init;
	p1Init.initialX = settings->GetFloat("P1_INITIAL_X");
	p1Init.initialY = settings->GetFloat("P1_INITIAL_Y");
	p1Init.initialRotation = settings->GetFloat("P1_INITIAL_ROTATION");
	p1Init.spritePath = "./images/handthrow.png";
	p1Init.ballSpawnPositionOffset = settings->GetFloat("P1_BALL_SPAWN_POSITION_OFFSET");
	p1Init.ballSpawnRotationOffset = settings->GetFloat("P1_BALL_SPAWN_ROTATION_OFFSET");
	p1Init.invertX = false;

	PlayerInitialisers p2Init;
	p2Init.initialX = settings->GetFloat("P2_INITIAL_X");
	p2Init.initialY = settings->GetFloat("P2_INITIAL_Y");
	p2Init.initialRotation = settings->GetFloat("P2_INITIAL_ROTATION");
	p2Init.spritePath = "./images/handthrow2.png";
	p2Init.ballSpawnPositionOffset = settings->GetFloat("P2_BALL_SPAWN_POSITION_OFFSET");
	p2Init.ballSpawnRotationOffset = settings->GetFloat("P2_BALL_SPAWN_ROTATION_OFFSET");
	p2Init.invertX = true;

	PlayerHand p1 = PlayerHand(this, p1Init);
	PlayerHand p2 = PlayerHand(this, p2Init);

	p1.SetControls(p1Controls);
	p2.SetControls(p2Controls);
	
	players.push_back(p1);
	players.push_back(p2);
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

			if ( CollisionCheck::CheckRectangleCollision(balls[i].GetCollider(), cup1.GetRimCollider()) &&  balls[i].IsFalling())
			{
				players[0].TakeADrink();
				balls[i].Kill();
			}
			else if ( CollisionCheck::CheckRectangleCollision(balls[i].GetCollider(), cup1.GetCupCollider()) )
			{
				//cout << "Hit Outside of CUP!!!" << endl;
				balls[i].ReboundOffCup();
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