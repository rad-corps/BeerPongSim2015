#pragma once

#include "Rect.h"

class CollisionCheck
{
public:
	~CollisionCheck(void);

	static bool CheckRectangleCollision(Rect r1_, Rect r2_, unsigned int colliderSprite = 0);



private:
	CollisionCheck(void);
};

