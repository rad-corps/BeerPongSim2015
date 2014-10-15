#include "Ball.h"
#include <iostream>
#include "Consts.h"
#include <cmath>

#define PI 3.14159265

using namespace std;
using namespace bp_ball;

Ball::Ball(Vector2 pos_, float angle_, float velocity_)
{
	velocity.SetMagnitude(velocity_);
	float radians = (angle_ - 90) * PI/180;
	velocity.SetAngle(radians);
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/pong.png",width, height, true);
	pos = pos_;
	active = true;
	ballTimer = 0;
	bounceCount = 0;
	dir_mod = 1;
}


Ball::~Ball()
{
}

bool Ball::Active()
{
	return active;
}

void Ball::Kill()
{
	active = false;
}

void Ball::ReboundOffCup()
{
	velocity.x = -velocity.x;
}

bool Ball::IsFalling()	
{
	return velocity.y < 0;
}

Rect
Ball::GetCollider()
{
	//todo grab bottom left of ball
	return Rect(pos, width, height);
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
		if(pos.y <  settings->GetInt("BAR_BOUNCE_HEIGHT") + height*0.5f && ballTimer > 0.05f)
		{
			velocity.y = -(velocity.y * settings->GetFloat("BOUNCE_LOSS"));
			bounceCount++;
			ballTimer = 0;												//Assists in stopping ball getting trapped between screen - thanks Gravity
		}
		
		velocity.y -= settings->GetFloat("GRAVITY") * delta_;
		pos += velocity;

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
