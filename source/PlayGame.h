#pragma once
#include "GAMESTATE.h"
#include "PlayerHand.h"
#include "PlayerHandObserver.h"
#include <vector>
#include "Ball.h"
#include "Cup.h"

class PlayGame : public GAMESTATE, public PlayerHandObserver
{
public:
	PlayGame();
	~PlayGame();

	void Update();
	void Draw();

	virtual void ThrowBall(Vector2 pos_, float angle_, float velocity_);
	virtual void CalculateTrajectory(Vector2 pos_, float angle_, float velocity_, int player_, int numBalls_);

private:
	FileSettings* settings;
	std::vector<PlayerHand> players;
	std::vector<Ball> balls;
	std::vector<Cup> cups;
	//Ball *ball;

	std::vector<Ball> p1Trajectory;
	std::vector<Ball> p2Trajectory;

	Ball offScreenBall;

	bool p1ShowTrajectory;
	bool p2ShowTrajectory;

	bool paused;
};

