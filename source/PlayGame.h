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

private:
	FileSettings* settings;
	std::vector<PlayerHand> players;
	std::vector<Ball> balls;
	Cup cup1;
	//Ball *ball;
};

