#include "Cup.h"
#include "AIE.h"

Cup::Cup(void)
{
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/pong_cup_v1.png", settings->GetInt("CUP_W"), settings->GetInt("CUP_H"), true);
	cupPos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
	rimPos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY") + settings->GetInt("CUP_H")/2);
	cupCollider = Rect(cupPos, settings->GetInt("CUP_W"), settings->GetInt("CUP_H"));
	rimCollider = Rect(rimPos, settings->GetInt("CUP_W"), 1);
}

Cup::Cup(CupInitialiser ci_)
{
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/pong_cup_v1.png", ci_.width, ci_.height, true);
	cupPos = ci_.pos;
	rimPos = Vector2(cupPos.x, cupPos.y + ci_.height/2);
	cupCollider = Rect(cupPos, ci_.width, ci_.height);
	
	//rim collider 1 pixel high, full width of the cup
	rimCollider = Rect(rimPos, ci_.width, 1);
	victim = ci_.victim;
}


Cup::~Cup(void)
{
}

Rect Cup::GetCupCollider()
{
	return cupCollider;
}

Rect Cup::GetRimCollider()
{
	return rimCollider;
}

void Cup::Update(float delta_)
{
	MoveSprite(spriteID, cupPos.x, cupPos.y);
}

void Cup::Draw()
{
	DrawSprite(spriteID);
}