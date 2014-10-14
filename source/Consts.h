#pragma once

#include <string>

using namespace std;

//const int SCREEN_W = 512;
//const int SCREEN_H = 512;
//
//
////just chucked this namespace in so i dont need to use 5000 character long variable names
//namespace bp_ph //beer pong player hand
//{
enum DRUNK_ZONE{
	DRUNK_ZONE_NERVOUS,
	DRUNK_ZONE_GAME_ON_MOLE,
	DRUNK_ZONE_TOO_FN_DRUNK,
	DRUNK_ZONE_END,
};

enum Y_DIR
{
	Y_DIR_UP,
	Y_DIR_DOWN
};
//
//	//so there is always some movement even from the start. 
//	const float MIN_DRUNKENNESS_MOVEMENT_MULTI = 10.f; 
//
//	//if we are in the zone, divide actual drunkenness by IN_THE_ZONE_DIVIDER
//	const float IN_THE_ZONE_DIVIDER = 4.f;
//
//	//speed of hand rotation via user input
//	const float ROTATION_SPEED = 200.f;
//
//	const float THROW_VELOCITY_MULTI = 10.f;
//}

namespace bp_ball
{
	//Modifies gravity effect
	//const float gravityMod = 3.0f;

	//Modifies mass of ball - lighter = more bounce
	//const float mass = 100.0f;				//Decrease to increase bounce

	//Increase/Decrease horizontal velocity
	//const float velocityModifier = 20.0f;

	//Dims of ball - Ensure pwr^2
	const int width = 16;
	const int height = 16;
}