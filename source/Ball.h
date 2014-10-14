///File:		Ball.h
///Brief:		Ball header file

#pragma once
#ifndef BALL_H
#define BALL_H

#include "Vector.h"
#include "AIE.h"
#include "FileSettings.h"

class Ball
{
public:
	Ball(Vector2 pos_, float angle_, float velocity_);
	~Ball();

	void Update(float delta_);
	void Draw();

private:
	FileSettings *settings;
	unsigned int spriteID;
	Vector2 pos;
	float angle;
	float velocityX;
	float velocityY;
	bool active;
	float ballTimer;
	
	int bounceCount;

	//New grav calc
	float gravity;
	float worldMass;

	int dir_mod;
};

#endif	//	BALL_H
