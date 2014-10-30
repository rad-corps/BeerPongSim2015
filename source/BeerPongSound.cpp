#include "BeerPongSound.h"

//init statics
int BeerPongSound::soundCounter = 0;
std::vector<HSTREAM> BeerPongSound::ballBounceSounds = std::vector<HSTREAM>();
HSTREAM BeerPongSound::ballInCupSound = 0;
HSTREAM BeerPongSound::throwPowerSound0 = 0;
HSTREAM BeerPongSound::throwPowerSound1 = 0;
HSTREAM BeerPongSound::throwSound = 0;
HSTREAM BeerPongSound::ambience = 0;
HSTREAM BeerPongSound::burp = 0;
HSTREAM BeerPongSound::canOpen = 0;
HSTREAM BeerPongSound::cheer = 0;



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
	BASS_ChannelPlay(ballInCupSound, true);
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
	BASS_ChannelPlay(throwSound, true);
}

void BeerPongSound::PlayAmbience()
{
	BASS_ChannelPlay(ambience, true);
}

void BeerPongSound::StopAmbience()
{
	BASS_ChannelStop(ambience);
}

void BeerPongSound::PlayBurp()
{
	BASS_ChannelPlay(burp, true);
}

void BeerPongSound::PlayCan()
{
	BASS_ChannelPlay(canOpen, true);
}

void BeerPongSound::PlayCheer()
{
	BASS_ChannelPlay(cheer, true);
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
	ambience = BASS_StreamCreateFile(false,"./sound/pub.mp3",0,0,0);
	burp = BASS_StreamCreateFile(false,"./sound/burpy.wav",0,0,0);
	canOpen = BASS_StreamCreateFile(false,"./sound/can-open-1.mp3",0,0,0);
	cheer= BASS_StreamCreateFile(false,"./sound/cheering.mp3",0,0,0);

	//can-open-1.mp3

	for ( int i = 0 ; i < ballBounceSounds.size(); ++i )
	{
		BASS_ChannelSetAttribute(ballBounceSounds[i], BASS_ATTRIB_VOL, 0.3f);
	}

	//set volume of channels
	BASS_ChannelSetAttribute(ballInCupSound, BASS_ATTRIB_VOL, 0.3f);
	BASS_ChannelSetAttribute(throwPowerSound0, BASS_ATTRIB_VOL, 0.3f);
	BASS_ChannelSetAttribute(throwPowerSound1, BASS_ATTRIB_VOL, 0.3f);
	BASS_ChannelSetAttribute(throwSound, BASS_ATTRIB_VOL, 0.3f);
	BASS_ChannelSetAttribute(ambience, BASS_ATTRIB_VOL, 0.4f);
	BASS_ChannelSetAttribute(burp, BASS_ATTRIB_VOL, 0.9f);
	BASS_ChannelSetAttribute(canOpen, BASS_ATTRIB_VOL, 0.9f);
	BASS_ChannelSetAttribute(cheer, BASS_ATTRIB_VOL, 0.9f);
}
