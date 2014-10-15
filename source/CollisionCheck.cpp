#include "CollisionCheck.h"
#include "AIE.h"


CollisionCheck::CollisionCheck(void)
{
}


CollisionCheck::~CollisionCheck(void)
{
}

//r2_ is cup
bool CollisionCheck::CheckRectangleCollision(Rect r1_, Rect r2_, unsigned int colliderSprite_ )
{
	//cout << "r1_ - " << r1_.ToString() << endl;
	//cout << "r2_ - " << r2_.ToString() << endl;
	if (r1_.Right() < r2_.Left() 
		|| r2_.Right() < r1_.Left() 
		|| r1_.Bottom() > r2_.Top() 
		|| r1_.Top() < r2_.Bottom())
		
		return false;
	return true;
}