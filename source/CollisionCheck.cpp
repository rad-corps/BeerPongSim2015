#include "CollisionCheck.h"
#include "AIE.h"


CollisionCheck::CollisionCheck(void)
{
}


CollisionCheck::~CollisionCheck(void)
{
}

bool CollisionCheck::CheckRectangleCollision(Rect r1_, Rect r2_, unsigned int colliderSprite_ )
{
	return !(r2_.Left() > r1_.Right() || 
           r2_.Right() < r1_.Left() || 
		   r2_.Top() > r1_.Bottom() ||
		   r2_.Bottom() < r1_.Top());

}