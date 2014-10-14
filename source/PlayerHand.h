#pragma once

#include "Vector.h"
#include "Consts.h"
#include "AIE.h"
#include "PlayerHandObserver.h"
#include "FileSettings.h"

const float HAND_SPEED = 250.f;
const float INITIAL_ROTATION = 270.f;
const float INITIAL_X = 20.f;
const float INITIAL_Y = 20.f;



class PlayerHand
{
public:
	PlayerHand(PlayerHandObserver* observer_);
	~PlayerHand(void);

	void Update(float delta_);
	void Draw();
	void RegisterObserver(PlayerHandObserver* observer_);
	DRUNK_ZONE GetCurrentZone();

private:

	void RotateHand(float delta_, bool clockwise_);

	string DrunkZoneToString(DRUNK_ZONE dz_);	
	Vector2 handPos; //locked x Axis
	float handRotation; //limits?
	//unsigned int handSprite;
	unsigned int handSpriteTest;
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
	void IncreaseDrunkennessForTesting();
	void DecreaseDrunkennessForTesting();

	PlayerHandObserver* observer;

	bool throwButtonHeld;
	float throwVelocity;

	FileSettings* settings;
};

