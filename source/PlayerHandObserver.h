#pragma once 
#include "Vector.h"

class PlayerHandObserver
{
public:
	//virtual ~PlayerHandObserver();
	virtual void ThrowBall(Vector2 pos_, float angle_, float velocity_) = 0;
};