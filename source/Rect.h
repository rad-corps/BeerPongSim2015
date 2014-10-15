#pragma once
#include "Vector.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

struct Rect
{
	float width;
	float height; 
	Vector2 centre; 

	float Left()
	{
		return centre.x - (width / 2);
	}

	float Right()
	{
		return centre.x + (width / 2);
	}

	float Bottom()
	{
		return centre.y - (height / 2);
	}

	float Top()
	{
		return centre.y + (height / 2);
	}

	//dont allow the user of the class to make a dodgy rectangle
	Rect(Vector2 centre_, float width_, float height_)
	{
		centre = centre_;
		width = width_;
		height = height_;
	}
	Rect(){}

	std::string ToString()
	{
		std::ostringstream out;
		out //<< std::setprecision(1) 
			<< "Left: " << Left() << "\t" 
			<< "Right: " << Right() << "\t" 
			<< "Top: " << Top() << "\t" 
			<< "Bottom: " << Bottom(); 

		return out.str();
	}

	
};