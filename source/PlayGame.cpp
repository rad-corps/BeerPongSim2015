#include "PlayGame.h"
#include "CollisionCheck.h"
#include "PlayerControls.h"


PlayGame::PlayGame()
{
	//init file settings
	settings = FileSettings::Instance();

	//initialise pause key state
	paused = false;
	
	//set initial game state
	stateSelection = GAME_STATES::PLAYING_GAME;
	
	//setup background image
	backgroundImage = CreateSprite("./images/bar-02.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true);
	MoveSprite(backgroundImage, settings->GetInt("SCREEN_W")*0.5f, settings->GetInt("SCREEN_H")*0.5f);

	//initialise balls for trajectory
	for (int i = 0; i < 20; ++i )
	{
		p1Trajectory.push_back(Ball());
	}
	for (int i = 0; i < 20; ++i )
	{
		p2Trajectory.push_back(Ball());
	}
	p1ShowTrajectory = false;
	p2ShowTrajectory = false;

	offScreenBall = Ball();
	offScreenBall.Init(Vector2(-100.f, -100.f), 0.f, 0.f);
	
	
	//setup the control layout
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

	//create the drunkometers
	DrunkometerInitialisers drunkoInit1;
	DrunkometerInitialisers drunkoInit2;
	drunkoInit1.pos = Vector2(settings->GetFloat("DRUNKOMETER_1_X"), settings->GetFloat("DRUNKOMETER_1_Y"));
	drunkoInit2.pos = Vector2(settings->GetFloat("DRUNKOMETER_2_X"), settings->GetFloat("DRUNKOMETER_2_Y"));	
	Drunkometer drunko1 = Drunkometer(drunkoInit1);
	Drunkometer drunko2 = Drunkometer(drunkoInit2);

	//create the hands/players
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

	PlayerHand p1 = PlayerHand(this, p1Init, drunko1);
	PlayerHand p2 = PlayerHand(this, p2Init, drunko2);
	p1.SetControls(p1Controls);
	p2.SetControls(p2Controls);	
	players.push_back(p1);
	players.push_back(p2);

	//create the cups
	CupInitialiser ci1;
	CupInitialiser ci2;
	
	ci1.pos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
	ci1.width = settings->GetFloat("CUP_W");
	ci1.height = settings->GetFloat("CUP_H");
	ci1.victim = 1;//PLAYER 2 DRINKS if ball goes in this cup

	ci2.pos = Vector2(settings->GetFloat("CUP2_POSX"), settings->GetFloat("CUP2_POSY"));
	ci2.width = settings->GetFloat("CUP_W");
	ci2.height = settings->GetFloat("CUP_H");
	ci2.victim = 0;//PLAYER 1 DRINKS if ball goes in this cup

	cups.push_back(Cup(ci1));
	cups.push_back(Cup(ci2));
}


PlayGame::~PlayGame()
{
}

void PlayGame::Update()
{
	//handle pause state
	if ( IsKeyDown(KEY_P) )
	{
		paused = true;
	}

	if ( IsKeyDown(KEY_SPACE) )
	{
		paused = false;
	}

	if ( paused )
	{
		GetDeltaTime();
		return;
	}
	
	float delta = GetDeltaTime();

	for (int i = 0; i < players.size(); ++i)
	{
		players[i].Update(delta);
	}

	//each ball
	for(int i = 0; i < balls.size(); i++)
	{
		//update/move it
		if ( balls[i].Active() ) 
		{
			balls[i].Update(delta);

			//did it hit a cup?
			for ( int cupNum = 0; cupNum < cups.size(); ++cupNum ) 
			{
				if ( CollisionCheck::CheckRectangleCollision(balls[i].GetCollider(), cups[cupNum].GetRimCollider()) &&  balls[i].IsFalling())
				{
					players[cups[cupNum].victim].TakeADrink();
					balls[i].Kill();
				}
				else if ( CollisionCheck::CheckRectangleCollision(balls[i].GetCollider(),  cups[cupNum].GetCupCollider()) )
				{
					//cout << "Hit Outside of CUP!!!" << endl;
					balls[i].ReboundOffCup();
				}
			}
		}
	}

	for ( int i = 0; i < cups.size(); ++i )
	{
		cups[i].Update(delta);
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

	for (int i = 0; i < cups.size(); ++i )
	{
		cups[i].Draw();
	}

	if ( p1ShowTrajectory )
	{
		for ( int i = 0; i < p1Trajectory.size(); ++i )
		{			
			p1Trajectory[i].Draw();
		}
	}
	
	if ( p2ShowTrajectory )
	{
		for ( int i = 0; i < p2Trajectory.size(); ++i )
		{
			p2Trajectory[i].Draw();
		}
	}

	p1ShowTrajectory = false;
	p2ShowTrajectory = false;
	
}

void PlayGame::ThrowBall(Vector2 pos_, float angle_, float velocity_)
{
	Ball ball = Ball(pos_, angle_, velocity_);
	balls.push_back(ball);
}

void PlayGame::CalculateTrajectory(Vector2 pos_, float angle_, float velocity_, int player_, int numBalls_)
{
	std::vector<Ball>* trajectoryPtr;
	
	if ( player_ == 0 )
	{
		p1ShowTrajectory = true;
		trajectoryPtr = &p1Trajectory;
	}
	else
	{
		p2ShowTrajectory = true;
		trajectoryPtr = &p2Trajectory;
	}

	//clear the balls
	for (int i = 0; i < (*trajectoryPtr).size(); ++i )
	{
		//(*trajectoryPtr)[i].CopyPhisicalProperties(offScreenBall);
		(*trajectoryPtr)[i].Kill();
	}

	//set the first element
	(*trajectoryPtr)[0].Init(pos_, angle_, velocity_);
	
	//start from the 2nd element (first one has been set)
	for (int i = 1; i < numBalls_; ++i )
	{
		(*trajectoryPtr)[i].CopyPhisicalProperties((*trajectoryPtr)[i - 1]);
		(*trajectoryPtr)[i].Update(0.035f);
	}
	return;
}