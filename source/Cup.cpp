#include "Cup.h"
#include "AIE.h"

Cup::Cup(void)
{
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/pong_cup_v1.png", settings->GetInt("CUP_W"), settings->GetInt("CUP_H"), true);
	cupPos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
	rimPos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY") + settings->GetInt("CUP_H")/2);
	cupCollider = Rect(cupPos, settings->GetInt("CUP_W"), settings->GetInt("CUP_H"));
	rimCollider = Rect(rimPos, settings->GetInt("CUP_W") * 0.9, 1);
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
	MoveSprite(spriteID, settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
}

void Cup::Draw()
{
	DrawSprite(spriteID);
}