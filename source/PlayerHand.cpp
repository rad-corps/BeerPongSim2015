#include "PlayerHand.h"
#include "AIE.h"
#include "MathHelpers.h"
#include <iostream>

PlayerHand::PlayerHand(PlayerHandObserver* observer_, PlayerInitialisers initialisers_)
{
	settings = FileSettings::Instance();
	handSpriteTest = CreateSprite( initialisers_.spritePath.c_str(), settings->GetInt("HAND_W"), settings->GetInt("HAND_H"), true );
	handPos = Vector2(initialisers_.initialX,initialisers_.initialY);
	
	invertX = initialisers_.invertX;

	RotateSprite(handSpriteTest, initialisers_.initialRotation);
	handRotation = 90.f;//TODO fix this hard code
	//handRotation = INITIAL_ROTATION;
	drunkenness = 0.f;
	currentInvoluntaryMovementDuration = 0.f;
	involuntaryMovementDir = Y_DIR::Y_DIR_UP;
	RegisterObserver(observer_);

	throwButtonHeld = false;
	throwButtonTimer = 0.f;
	throwButtonActive = true;

	ballSpawnPositionOffset = initialisers_.ballSpawnPositionOffset;
	ballSpawnRotationOffset = initialisers_.ballSpawnRotationOffset;
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

void PlayerHand::SetControls(PlayerControls controls_)
{
	controls = controls_;
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

void PlayerHand::ThrowBall()
{
	//yeah its a hack, sorry!
	float tempHandRot = 0.f;
	if ( invertX ) 
		tempHandRot = handRotation - 180;
	else
		tempHandRot = handRotation;

	throwButtonHeld = false;
	//calculate initial ball position
	Vector2 ballOffset;		
	
	float handRotationInRadians = (tempHandRot * DEG_TO_RAD) + ballSpawnRotationOffset;
	ballOffset.SetAngle(handRotationInRadians);
	ballOffset.SetMagnitude(ballSpawnPositionOffset);
	
	ballOffset += handPos;
	observer->ThrowBall(ballOffset, tempHandRot, throwVelocity);
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
	if ( IsKeyDown(controls.up) ) 
	{
		handPos.y += (settings->GetFloat("HAND_SPEED") * delta_);
		if ( handPos.y > settings->GetFloat("SCREEN_H") - 16 ) 
			handPos.y = settings->GetFloat("SCREEN_H") - 16;
	}
	if ( IsKeyDown(controls.down) ) 
	{
		handPos.y -= (settings->GetFloat("HAND_SPEED") * delta_);
		if ( handPos.y < settings->GetFloat("BAR_BOUNCE_HEIGHT") + 16 ) 
			handPos.y = settings->GetFloat("BAR_BOUNCE_HEIGHT") + 16;
	}
	if ( IsKeyDown(controls.anticlockwise) ) 
	{
		RotateHand(delta_, false);
	}
	if ( IsKeyDown(controls.clockwise) ) 
	{
		RotateHand(delta_, true);
	}
	//if ( IsKeyDown(KEY_RIGHT) )
	//{
	//	IncreaseDrunkennessForTesting(delta_);
	//}
	//if ( IsKeyDown(KEY_LEFT) )
	//{
	//	DecreaseDrunkennessForTesting(delta_);
	//}
	
	//inactive if user has held it longer than MAX_VELOCITY_CAP_TIME
	if ( throwButtonActive )
	{
		if ( IsKeyDown(controls.throwBall))
		{
			//if throw button only just pressed this frame
			if ( !throwButtonHeld ) 
			{
				throwButtonHeld = true;
				throwVelocity = 0.f;			
				throwButtonTimer = 0.f;
			}

			//add to velocity and held timer
			throwVelocity += delta_ * settings->GetFloat("THROW_VELOCITY_MULTI");
			throwButtonTimer += delta_;

			//if throw button still held, but we have hit the max timer.
			if ( throwButtonTimer > settings->GetFloat("MAX_VELOCITY_CAP_TIME") ) 
			{
				throwButtonActive = false;
				ThrowBall();
			}
		}	
		else if (throwButtonHeld) //if throw button was just released
		{		
			ThrowBall();
		}
	}
	//if the throw key is not down, then reactivate the throw button
	else if ( !IsKeyDown(controls.throwBall) )
	{
		throwButtonActive = true;
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
void PlayerHand::IncreaseDrunkennessForTesting(float delta_)
{
	drunkenness += (delta_ * 20);
}

void PlayerHand::TakeADrink()
{
	drunkenness += settings->GetFloat("DRUNKOMETER_INCREASER");
}

void PlayerHand::DecreaseDrunkennessForTesting(float delta_)
{
	drunkenness -= (delta_ * 20);
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