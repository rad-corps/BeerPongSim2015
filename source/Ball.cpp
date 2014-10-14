#include "Ball.h"
#include <iostream>
#include "Consts.h"
#include <cmath>

#define PI 3.14159265

using namespace std;
using namespace bp_ball;

Ball::Ball(Vector2 pos_, float angle_, float velocity_)
{
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/pong.png",width, height, true);
	pos = pos_;
	angle = angle_;
	velocityX = velocity_ * velocityModifier;
	velocityY = velocity_ * velocityModifier;
	active = true;

	ballTimer = 0;
	bounceCount = 0;

	gravity = -9.81f * gravityMod;
	worldMass = 1000.0f;												//Leave as is - go mess with 'mass' in Consts.h.

	dir_mod = 1;
}


Ball::~Ball()
{
}

void Ball::Update(float delta_)
{
	ballTimer += delta_;

	if(pos.x < 0 - width * 0.5f || pos.x > settings->GetInt("SCREEN_W") + width * 0.5f)
	{
		active = false;
	}

	if(pos.y < -10)														//Nothing technical about it.. ball has fallen off screen
	{
		active = false;
	}

	if(active)
	{
		if(pos.y < 0 + height*0.5f && ballTimer > 0.5f)
		{
			velocityY = (velocityY)*(mass-worldMass)/(mass+worldMass);
			bounceCount++;
			ballTimer = 0;												//Assists in stopping ball getting trapped between screen - thanks Gravity
		}

		//Resolve motion component - now with angles
		pos.x += (velocityX * cos((angle-90)*PI/180)) * delta_;

		if(angle <= 90)
		{
			velocityY = velocityY - gravity * delta_;
			pos.y -= (velocityY * sin((angle+90)*PI/180)) * delta_ - gravity * (delta_*delta_);
		}else{
			velocityY = velocityY + gravity * delta_;
			pos.y += (velocityY * sin((angle-90)*PI/180)) * delta_ - gravity * (delta_*delta_);
		}

		MoveSprite(spriteID, pos.x, pos.y);
	}
}

void Ball::Draw()
{
	if(active)
	{
		DrawSprite(spriteID);
	}
}
