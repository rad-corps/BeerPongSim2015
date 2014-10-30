#pragma once

#include <vector>
#include "bass.h"

class BeerPongSound
{
public:	
	~BeerPongSound(void);

	static void Initialise();
	static void PlayBallBounceSound();
	static void PlayBallInCupSound();
	static void PlayThrowPower(int player_);
	static void StopThrowPower(int player_);
	static void PlayThrowBall();
	static void PlayAmbience();
	static void StopAmbience();


private:
	BeerPongSound(void);
	static int soundCounter;
	static std::vector<HSTREAM> ballBounceSounds;
	static HSTREAM ballInCupSound;
	static HSTREAM throwPowerSound0;
	static HSTREAM throwPowerSound1;
	static HSTREAM throwSound;
	static HSTREAM ambience;
};

