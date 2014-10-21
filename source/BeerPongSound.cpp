#include "BeerPongSound.h"

//init statics
int BeerPongSound::soundCounter = 0;
std::vector<HSTREAM> BeerPongSound::ballBounceSounds = std::vector<HSTREAM>();
HSTREAM BeerPongSound::ballInCupSound = 0;
HSTREAM BeerPongSound::throwPowerSound0 = 0;
HSTREAM BeerPongSound::throwPowerSound1 = 0;
HSTREAM BeerPongSound::throwSound = 0;

BeerPongSound::BeerPongSound(void)
{
}



BeerPongSound::~BeerPongSound(void)
{
}

void BeerPongSound::PlayBallBounceSound()
{
	BASS_ChannelPlay(ballBounceSounds[soundCounter%5], false);
	++soundCounter;
}

void BeerPongSound::PlayBallInCupSound()
{
	BASS_ChannelPlay(ballInCupSound, false);
}

void BeerPongSound::PlayThrowPower(int player_)
{
	if ( player_ == 0 )
		BASS_ChannelPlay(throwPowerSound0, true);
	else
		BASS_ChannelPlay(throwPowerSound1, true);
}

void BeerPongSound::StopThrowPower(int player_)
{
	if ( player_ == 0 )
		BASS_ChannelStop(throwPowerSound0);
	else 
		BASS_ChannelStop(throwPowerSound1);
}

void BeerPongSound::PlayThrowBall()
{
	BASS_ChannelPlay(throwSound, false);
}

void BeerPongSound::Initialise()
{
	BASS_Init(-1,44100,0,0,0);

	//create the ball bounce sounds
	ballBounceSounds.push_back(BASS_StreamCreateFile(false,"./sound/pong1.wav",0,0,0));
	ballBounceSounds.push_back(BASS_StreamCreateFile(false,"./sound/pong2.wav",0,0,0));
	ballBounceSounds.push_back(BASS_StreamCreateFile(false,"./sound/pong3.wav",0,0,0));
	ballBounceSounds.push_back(BASS_StreamCreateFile(false,"./sound/pong4.wav",0,0,0));
	ballBounceSounds.push_back(BASS_StreamCreateFile(false,"./sound/pong5.wav",0,0,0));

	ballInCupSound = BASS_StreamCreateFile(false,"./sound/incup.wav",0,0,0);

	throwPowerSound0 = BASS_StreamCreateFile(false,"./sound/throwpower.wav",0,0,0);
	throwPowerSound1 = BASS_StreamCreateFile(false,"./sound/throwpower.wav",0,0,0);
	throwSound = BASS_StreamCreateFile(false,"./sound/pop.wav",0,0,0);

}
