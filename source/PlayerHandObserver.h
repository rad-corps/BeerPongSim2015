#pragma once 
#include "Vector.h"

class PlayerHandObserver
{
public:
	//virtual ~PlayerHandObserver();
	virtual void ThrowBall(Vector2 pos_, float angle_, float velocity_) = 0;
	virtual void CalculateTrajectory(Vector2 pos_, float angle_, float velocity_, int player_, int numBalls_) = 0;
	virtual void GameOverEvent(int loser_) = 0;
};