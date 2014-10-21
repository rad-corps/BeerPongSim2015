#include "Drunkometer.h"
#include "MathHelpers.h"


Drunkometer::Drunkometer(void)
{
	settings = FileSettings::Instance();


}

Drunkometer::Drunkometer(DrunkometerInitialisers di_)
{
	settings = FileSettings::Instance();
	drunkoBarSprite = CreateSprite("./images/drunkometer_v1.1.png", settings->GetInt("DRUNKOMETER_W"), settings->GetInt("DRUNKOMETER_H"), true);
	drunkoMugSprite = CreateSprite("./images/beermug_drunkometer.png", settings->GetInt("DRUNKOMETER_MUG_W"), settings->GetInt("DRUNKOMETER_MUG_H"), true);
	pos = di_.pos;
}


Drunkometer::~Drunkometer(void)
{

}



void Drunkometer::Update(float drunkenness_)
{
	drunkenness = drunkenness_;
	MoveSprite(drunkoBarSprite, pos.x, pos.y);
	
	//find starting/end points and lerp between
	float mugXStartingPoint = pos.x - settings->GetInt("DRUNKOMETER_W") /2;
	float mugXEndPoint = pos.x + settings->GetInt("DRUNKOMETER_W") /2;
	float mugXPos = Lerp(mugXStartingPoint, mugXEndPoint, drunkenness/100.f);
	MoveSprite(drunkoMugSprite, mugXPos, pos.y - 10);
}

void Drunkometer::Draw()
{
	////write stuff about things
	//SetFont( "./fonts/invaders.fnt" );
	//
	////display drunkometer
	//string drunkStr = "Drunkometer: ";
	//drunkStr += to_string(drunkenness) + " - " +  DrunkZoneToString(GetCurrentZone());
	//DrawString( drunkStr.c_str(),	pos.x,	pos.y, 0.8f, SColour(0,0,0,255));

	//SetFont( nullptr );
	DrawSprite(drunkoBarSprite);
	DrawSprite(drunkoMugSprite);
}


DRUNK_ZONE Drunkometer::GetCurrentZone()
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

string Drunkometer::DrunkZoneToString(DRUNK_ZONE dz_)
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