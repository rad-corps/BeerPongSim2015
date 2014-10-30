#pragma once
#include "GAMESTATE.h"
#include "PlayerHand.h"
#include "PlayerHandObserver.h"
#include <vector>
#include "Ball.h"
#include "Cup.h"
#include "StateObserver.h"

class PlayGame : public GAMESTATE, public PlayerHandObserver
{
public:
	PlayGame(StateObserver* observer_);
	~PlayGame();

	void Update();
	void Draw();

	virtual void ThrowBall(Vector2 pos_, float angle_, float velocity_);
	virtual void CalculateTrajectory(Vector2 pos_, float angle_, float velocity_, int player_, int numBalls_);
	virtual void GameOverEvent(int loser_);

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

	StateObserver* observer;
};

