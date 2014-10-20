#pragma once

#include "Vector.h"
#include "Consts.h"
#include "AIE.h"
#include "PlayerHandObserver.h"
#include "FileSettings.h"
#include "PlayerControls.h"
#include "Drunkometer.h"

//const float HAND_SPEED = 250.f;
//const float INITIAL_ROTATION = 270.f;
//const float INITIAL_X = 20.f;
//const float INITIAL_Y = 20.f;



class PlayerHand
{
public:
	PlayerHand(PlayerHandObserver* observer_, PlayerInitialisers initialisers_, Drunkometer drunkometer_);
	~PlayerHand(void);

	void Update(float delta_);
	void Draw();
	void RegisterObserver(PlayerHandObserver* observer_);
	
	void TakeADrink();
	void SetControls(PlayerControls controls_);
	void SetInitialisers(PlayerInitialisers init_);

private:

	void RotateHand(float delta_, bool clockwise_);
	void ThrowBall();

	
	Vector2 handPos; //locked x Axis
	float handRotation; //limits?
	//unsigned int handSprite;
	unsigned int handSpriteTest;
	
	Drunkometer drunkometer;
	float drunkenness;
	
	//involuntary movement y axis
	Y_DIR involuntaryMovementDir;
	float involuntaryMovementVelocity;
	float involuntaryMovementDuration;
	float currentInvoluntaryMovementDuration;

	//involuntary movement y axis calculation
	void CalculateInvoluntaryMovement();
	void DoInvoluntaryMovement();


	//Testing Functions
	void IncreaseDrunkennessForTesting(float delta_);
	void DecreaseDrunkennessForTesting(float delta_);

	

	PlayerHandObserver* observer;

	bool throwButtonHeld;
	bool throwButtonActive;
	float throwVelocity;
	float throwButtonTimer;

	FileSettings* settings;
	PlayerControls controls;

	float ballSpawnRotationOffset;
	float ballSpawnPositionOffset;

	bool invertX;
};

