///File:		Ball.h
///Brief:		Ball header file

#pragma once
#ifndef BALL_H
#define BALL_H

#include "Vector.h"
#include "AIE.h"
#include "FileSettings.h"
#include "Rect.h"

class Ball
{
public:
	Ball();
	Ball(Vector2 pos_, float angle_, float velocity_);
	~Ball();

	//rather than use a copy constructor, todo change later to copy ctor. 
	void CopyPhisicalProperties(const Ball& ball_);


	void Init(Vector2 pos_, float angle_, float velocity_);

	void Update(float delta_);
	void Draw();
	bool Active();
	void ReboundOffCup();
	bool IsFalling();
	void Kill();
	Rect GetCollider();

private:
	FileSettings *settings;
	unsigned int spriteID;
	
	Vector2 velocity;
	Vector2 pos;
	bool active;
	float ballTimer;
	int bounceCount;
	int dir_mod;

	bool trajectoryBall;
};

#endif	//	BALL_H
