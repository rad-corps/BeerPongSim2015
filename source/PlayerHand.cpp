#include "PlayerHand.h"
#include "AIE.h"
#include "MathHelpers.h"
#include <iostream>

PlayerHand::PlayerHand(PlayerHandObserver* observer_)
{
	settings = FileSettings::Instance();
	handSpriteTest = CreateSprite( "./images/hand_white_box.png", 32, 32, true );
	handPos = Vector2(30.f,settings->GetInt("SCREEN_H")*0.5f);
	
	RotateSprite(handSpriteTest, INITIAL_ROTATION);
	handRotation = 90.f;
	//handRotation = INITIAL_ROTATION;
	drunkenness = 0.f;
	currentInvoluntaryMovementDuration = 0.f;
	involuntaryMovementDir = Y_DIR::Y_DIR_UP;
	RegisterObserver(observer_);

	throwButtonHeld = false;
}


PlayerHand::~PlayerHand(void)
{
	//dont dare destroy the sprite here, because we are using copy constructors and stuff by not using pointers in PlayGame
	//DestroySprite(handSpriteTest);
}

void PlayerHand::RegisterObserver(PlayerHandObserver* observer_)
{
	observer = observer_;
}

void PlayerHand::Draw()
{
	//draw the hand
	DrawSprite( handSpriteTest);

	//write stuff about things
	SetFont( "./fonts/invaders.fnt" );
	
	//display drunkometer
	string drunkStr = "Drunkometer: ";
	drunkStr += to_string(drunkenness);
	DrawString( drunkStr.c_str(),	10,	settings->GetInt("SCREEN_H") - 2 , 0.5f);

	//display current zone
	string dzStr = DrunkZoneToString(GetCurrentZone());
	DrawString( dzStr.c_str(),	200,	settings->GetInt("SCREEN_H") - 2 , 0.5f);

	SetFont( nullptr );
}

void PlayerHand::Update(float delta_)
{
	if ( GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_END )
		return;



	//increase timer
	currentInvoluntaryMovementDuration += delta_;
	
	//recalculate if timer is done
	if  (currentInvoluntaryMovementDuration > involuntaryMovementDuration ) 
	{
		CalculateInvoluntaryMovement();
	}

	//HOW DRUNK ARE YA?? *hic*
	DoInvoluntaryMovement();	

	//do user input
	if ( IsKeyDown(KEY_W) ) 
	{
		handPos.y += (HAND_SPEED * delta_);
	}
	if ( IsKeyDown(KEY_S) ) 
	{
		handPos.y -= (HAND_SPEED * delta_);
	}
	if ( IsKeyDown(KEY_A) ) 
	{
		RotateHand(delta_, false);
	}
	if ( IsKeyDown(KEY_D) ) 
	{
		RotateHand(delta_, true);
	}
	if ( IsKeyDown(KEY_RIGHT) )
	{
		IncreaseDrunkennessForTesting();
	}
	if ( IsKeyDown(KEY_LEFT) )
	{
		DecreaseDrunkennessForTesting();
	}
	if ( IsKeyDown(KEY_LEFT_CONTROL))
	{
		if ( throwButtonHeld ) 
		{
			throwVelocity += delta_ * settings->GetFloat("THROW_VELOCITY_MULTI");
		}
		else
		{
			throwButtonHeld = true;
			throwVelocity = 0.f;
			throwVelocity += delta_ * settings->GetFloat("THROW_VELOCITY_MULTI");
		}
	}
	else if (throwButtonHeld)
	{
		throwButtonHeld = false;
		observer->ThrowBall(handPos, handRotation, throwVelocity);
	}

	//move sprite to final position
	MoveSprite( handSpriteTest,  handPos.x, handPos.y );
}

//rotation
void PlayerHand::RotateHand(float delta_, bool clockwise_)
{
	float rotationDifference = delta_ * settings->GetFloat("ROTATION_SPEED");
	if ( clockwise_ ) 
	{
		rotationDifference = -rotationDifference;
	}

	handRotation += rotationDifference;
	if ( handRotation > settings->GetFloat("ROTATION_MAX") )
	{
		handRotation = settings->GetFloat("ROTATION_MAX");
		return;
	}
	if (handRotation < settings->GetFloat("ROTATION_MIN") )
	{
		handRotation = settings->GetFloat("ROTATION_MIN");
		return;
	}
	RotateSprite(handSpriteTest, rotationDifference);
}

//these 2 functions are just here for testing
void PlayerHand::IncreaseDrunkennessForTesting()
{
	drunkenness += (GetDeltaTime() * 20);
}

void PlayerHand::TakeADrink()
{
	drunkenness += settings->GetFloat("DRUNKOMETER_INCREASER");
}

void PlayerHand::DecreaseDrunkennessForTesting()
{
	drunkenness -= (GetDeltaTime() * 20);
	if ( drunkenness < 0.0f ) 
		drunkenness = 0.0f;
}

//called when its time to recalc movement velocity/direction
void PlayerHand::CalculateInvoluntaryMovement()
{
	float tempDrunkenness = settings->GetFloat("MIN_DRUNKENNESS_MOVEMENT_MULTI");

	//reset timer
	currentInvoluntaryMovementDuration = 0.f;

	//switch movement direction
	involuntaryMovementDir == Y_DIR::Y_DIR_DOWN ? involuntaryMovementDir = Y_DIR::Y_DIR_UP : involuntaryMovementDir = Y_DIR::Y_DIR_DOWN;

	//dont ever calc involuntary movement on drunkenness < MIN_DRUNKENNESS_MOVEMENT_MULTI
	if ( drunkenness >= settings->GetFloat("MIN_DRUNKENNESS_MOVEMENT_MULTI") )
		tempDrunkenness = drunkenness;

	//calculate involuntary movement
	involuntaryMovementVelocity = (tempDrunkenness / 600) * RandomPercentageAbove(0.5f);

	//calculate the duration of the movement 
	float drunkFraction = drunkenness / 100.f;
	involuntaryMovementDuration = Lerp(0.2f, 0.6f, drunkFraction);
}

//called once every frame
void PlayerHand::DoInvoluntaryMovement()
{
	float tempInvoluntaryMovementVelocity = involuntaryMovementVelocity;

	if ( GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_GAME_ON_MOLE )
		tempInvoluntaryMovementVelocity /= settings->GetFloat("IN_THE_ZONE_DIVIDER");

	involuntaryMovementDir == Y_DIR::Y_DIR_UP ? handPos.y += tempInvoluntaryMovementVelocity : handPos.y -= tempInvoluntaryMovementVelocity;
}


//Just a couple of helpers. Probably dont belong in PlayerHand class
DRUNK_ZONE PlayerHand::GetCurrentZone()
{
	if ( drunkenness >= settings->GetInt("DRUNK_ZONE_END") )
		return DRUNK_ZONE_END;
	if ( drunkenness >= settings->GetInt("DRUNK_ZONE_TOO_FN_DRUNK"))
		return DRUNK_ZONE_TOO_FN_DRUNK;
	if ( drunkenness >= settings->GetInt("DRUNK_ZONE_GAME_ON_MOLE"))
		return DRUNK_ZONE_GAME_ON_MOLE;
	if ( drunkenness >= settings->GetInt("DRUNK_ZONE_NERVOUS"))
		return DRUNK_ZONE_NERVOUS;
}

string PlayerHand::DrunkZoneToString(DRUNK_ZONE dz_)
{
	if ( dz_ == DRUNK_ZONE_NERVOUS ) 
		return "Nervous..";
	if ( dz_ == DRUNK_ZONE_GAME_ON_MOLE ) 
		return "Game On Mole!";
	if ( dz_ == DRUNK_ZONE_TOO_FN_DRUNK ) 
		return "Too F'N Drunk!";
	if ( dz_ == DRUNK_ZONE_END ) 
		return "Fell over!";
}