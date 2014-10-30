#pragma once

class StateObserver
{
public:
	virtual void GameOverEvent(int winner_) = 0;
};