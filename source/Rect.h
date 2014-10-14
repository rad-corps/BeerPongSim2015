#pragma once
#include "Vector.h"

struct Rect
{
	Vector2 tl;
	Vector2 tr;
	Vector2 bl;
	Vector2 br;

	float Left()
	{
		return tl.x;
	}

	float Right()
	{
		return tr.x;
	}

	float Bottom()
	{
		return bl.y;
	}

	float Top()
	{
		return tl.y;
	}

	//dont allow the user of the class to make a dodgy rectangle
	Rect(Vector2 bl_, int width_, int height_)
	{
		bl = bl_;
		br.y = bl.y;
		br.x = bl.x + width_;
		tr.y = bl.y + height_;
		tr.x = br.x;
		tl.x = bl.x;
		tl.y = tr.y;
	}
	Rect(){}

	
};