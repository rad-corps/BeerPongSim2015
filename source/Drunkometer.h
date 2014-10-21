#pragma once

#include "Vector.h"
#include "AIE.h"
#include "Consts.h"
#include "FileSettings.h"

struct DrunkometerInitialisers
{
	Vector2 pos;
};


class Drunkometer
{
public:
	Drunkometer();
	Drunkometer(DrunkometerInitialisers);
	~Drunkometer();

	void Update(float drunkenness_);
	void Draw();

	DRUNK_ZONE GetCurrentZone();

private:
	
	string DrunkZoneToString(DRUNK_ZONE dz_);	

	float drunkenness;
	Vector2 pos;
	FileSettings* settings;

	unsigned int drunkoBarSprite;
	unsigned int drunkoMugSprite;

};

