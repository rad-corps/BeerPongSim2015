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
	spriteID = CreateSprite("./images/Pongball_v1_bord_v2.png",settings->GetInt("PONG_DIAMETER"), settings->GetInt("PONG_DIAMETER"), true);
	Init(pos_, angle_, velocity_);
	active = true;
	trajectoryBall = false;
}

void Ball::CopyPhisicalProperties(const Ball& ball_)
{
	pos = ball_.pos;
	velocity = ball_.velocity;
	ballTimer = ball_.ballTimer;
	active = ball_.active;
}

void
Ball::Init(Vector2 pos_, float angle_, float velocity_)
{
	velocity.SetMagnitude(velocity_);
	float radians = (angle_ - 90) * PI/180;
	velocity.SetAngle(radians);
	pos = pos_;
	active = true;
	ballTimer = 0;
	bounceCount = 0;
	dir_mod = 1;
}

//must be initialised before using
Ball::Ball()
{
	settings = FileSettings::Instance();	
	trajectoryBall = true;
	spriteID = CreateSprite("./images/Pongball_v2.png",settings->GetInt("PONG_DIAMETER"), settings->GetInt("PONG_DIAMETER"), true);
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
	return Rect(pos, settings->GetInt("PONG_DIAMETER"), settings->GetInt("PONG_DIAMETER"));
}

void Ball::Update(float delta_)
{
	//increase time since ball has collided with the table
	ballTimer += delta_;

	//check for falling off screen
	if(pos.x < 0 - settings->GetInt("PONG_DIAMETER") * 0.5f || pos.x > settings->GetInt("SCREEN_W") + settings->GetInt("PONG_DIAMETER") * 0.5f)
	{
		active = false;
	}

	if(pos.y < -10)														//Nothing technical about it.. ball has fallen off screen
	{
		active = false;
	}

	if(active)
	{
		//if this ball is just showing the trajectory we dont want to worry about the timer as it can cause bugs
		//if ( trajectoryBall && pos.y <  settings->GetInt("BAR_BOUNCE_HEIGHT") + settings->GetInt("PONG_DIAMETER")*0.5f )
		//{
		//	velocity.y = -(velocity.y * settings->GetFloat("BOUNCE_LOSS"));
		//}
		
		//if we are a normal thrown ball
		if(!trajectoryBall && pos.y <  settings->GetInt("BAR_BOUNCE_HEIGHT") + settings->GetInt("PONG_DIAMETER")*0.5f && ballTimer > 0.05f)
		{
			velocity.y = -(velocity.y * settings->GetFloat("BOUNCE_LOSS"));
			bounceCount++;
			ballTimer = 0;												//Assists in stopping ball getting trapped between screen - thanks Gravity
			if (bounceCount >= settings->GetInt("MAX_BOUNCE_COUNT"))
				active = false;
		}
		
		if ( velocity.x > 0 ) velocity.x -= settings->GetFloat("AIR_RESISTANCE") * delta_;
		else velocity.x += settings->GetFloat("AIR_RESISTANCE") * delta_;
		velocity.y -= settings->GetFloat("GRAVITY") * delta_;
		pos += velocity * delta_;

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
