#include "PlayerHand.h"
#include "AIE.h"
#include "MathHelpers.h"
#include <iostream>

PlayerHand::PlayerHand(PlayerHandObserver* observer_, PlayerInitialisers initialisers_, Drunkometer drunkometer_)
{
	settings = FileSettings::Instance();
	handSpriteTest = CreateSprite( initialisers_.spritePath.c_str(), settings->GetInt("HAND_W"), settings->GetInt("HAND_H"), true );
	handPos = Vector2(initialisers_.initialX,initialisers_.initialY);
	
	invertX = initialisers_.invertX;
	
	if ( invertX ) player = 1 ;
	else player = 0;

	RotateSprite(handSpriteTest, initialisers_.initialRotation);
	handRotation = 90.f;//TODO fix this hard code
	//handRotation = INITIAL_ROTATION;
	drunkenness = 0.f;
	currentInvoluntaryMovementDuration = 0.f;
	currentInvoluntaryRotationDuration = 0.0f;
	involuntaryMovementDuration = 0.0f;

	involuntaryMovementDir = Y_DIR::Y_DIR_UP;
	RegisterObserver(observer_);

	throwButtonHeld = false;
	throwButtonTimer = 0.f;
	throwButtonActive = true;

	ballSpawnPositionOffset = initialisers_.ballSpawnPositionOffset;
	ballSpawnRotationOffset = initialisers_.ballSpawnRotationOffset;

	drunkometer = drunkometer_;


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

	drunkometer.Draw();
}

void PlayerHand::CalculateBallProperties(Vector2& ballOffset_, float& rotation_)
{
	//yeah its a hack, sorry!
	rotation_ = 0.f;
	if ( invertX ) 
		rotation_ = handRotation - 180;
	else
		rotation_ = handRotation;

	
	//calculate initial ball position	
	
	float handRotationInRadians = (rotation_ * DEG_TO_RAD) + ballSpawnRotationOffset;
	ballOffset_.SetAngle(handRotationInRadians);
	ballOffset_.SetMagnitude(ballSpawnPositionOffset);	
	ballOffset_ += handPos;
}

void PlayerHand::ThrowBall()
{
	Vector2 ballOffset;
	float temprotation;
	float velocity;
	CalculateBallProperties(ballOffset, temprotation);
	observer->ThrowBall(ballOffset, temprotation, throwVelocity);
}

void PlayerHand::CalculateTrajectory()
{
	Vector2 ballOffset;
	float temprotation;
	float velocity;
	CalculateBallProperties(ballOffset, temprotation);

	//how many balls do we want to show? 20 for game on, 10 for nervous, 5 for too fn drunk
	int numBalls;
	if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_NERVOUS )
		numBalls = 10;
	else if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_GAME_ON_MOLE )
		numBalls = 20;
	else if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_TOO_FN_DRUNK )
		numBalls = 5;

	observer->CalculateTrajectory(ballOffset, temprotation, throwVelocity, player, numBalls);
}

void PlayerHand::Update(float delta_)
{
	if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_END )
		return;

	//increase timer
	currentInvoluntaryMovementDuration += delta_;

	if ( drunkenness > 0.f )
		drunkenness -= delta_ * settings->GetFloat("SOBERING_UP_MULTI");
	
	//recalculate if timer is done
	if  (currentInvoluntaryMovementDuration > involuntaryMovementDuration ) 
	{
		CalculateInvoluntaryMovement();
	}

	//HOW DRUNK ARE YA?? *hic*
	DoInvoluntaryMovement(delta_);	

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
		RotateHand(delta_ * settings->GetFloat("ROTATION_SPEED"));
	}
	if ( IsKeyDown(controls.clockwise) ) 
	{
		RotateHand(delta_ * -settings->GetFloat("ROTATION_SPEED"));
	}
	
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
			else
			{
				CalculateTrajectory();
			}
		}	
		else if (throwButtonHeld) //if throw button was just released
		{		
			throwButtonHeld = false;
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

	//update the drunkometer
	drunkometer.Update(drunkenness);
}

//rotation
void PlayerHand::RotateHand(float speed_)
{
	float newHandRotation = handRotation + speed_;

	if ( newHandRotation > settings->GetFloat("ROTATION_MAX") )
	{		
		newHandRotation = settings->GetFloat("ROTATION_MAX");
	}
	if (newHandRotation < settings->GetFloat("ROTATION_MIN") )
	{
		newHandRotation = settings->GetFloat("ROTATION_MIN");
	}
	speed_ = newHandRotation - handRotation;
	handRotation = newHandRotation;
	RotateSprite(handSpriteTest, speed_);
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
	involuntaryMovementVelocity = (tempDrunkenness) * RandomPercentageAbove(0.5f);

	//calculate the duration of the movement 
	float drunkFraction = drunkenness / 100.f;
	involuntaryMovementDuration = Lerp(0.2f, 0.6f, drunkFraction);

	//TODO break off into another calculate function
	//switch rotation direction
	involuntaryRotationDir == ROT_DIR::ANTICLOCKWISE ? involuntaryRotationDir = ROT_DIR::CLOCKWISE : involuntaryRotationDir = ROT_DIR::ANTICLOCKWISE;
	
	//calculate involuntary rotation
	involuntaryRotationVelocity = (tempDrunkenness) * RandomPercentageAbove(0.25f);
}

//called once every frame
void PlayerHand::DoInvoluntaryMovement(float delta_)
{
	float tempInvoluntaryMovementVelocity = involuntaryMovementVelocity;

	if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_GAME_ON_MOLE )
		tempInvoluntaryMovementVelocity /= settings->GetFloat("IN_THE_ZONE_DIVIDER");

	involuntaryMovementDir == Y_DIR::Y_DIR_UP ? handPos.y += tempInvoluntaryMovementVelocity * delta_: handPos.y -= tempInvoluntaryMovementVelocity * delta_;

	//do rotation involuntary movement
	if ( drunkometer.GetCurrentZone() == DRUNK_ZONE::DRUNK_ZONE_TOO_FN_DRUNK )
	{
		if ( involuntaryRotationDir ==  ROT_DIR::CLOCKWISE )
			RotateHand(involuntaryRotationVelocity * delta_);
		else
			RotateHand(-involuntaryRotationVelocity * delta_);
	}
}


