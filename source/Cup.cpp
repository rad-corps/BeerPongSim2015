#include "Cup.h"
#include "AIE.h"

Cup::Cup(void)
{
	settings = FileSettings::Instance();
	spriteID = CreateSprite("./images/cup.png", settings->GetInt("CUP_W"), settings->GetInt("CUP_H"), true);
	pos = Vector2(settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
	collider = Rect(pos, settings->GetInt("CUP_W"), settings->GetInt("CUP_H"));
}


Cup::~Cup(void)
{
}

Rect Cup::GetCollider()
{
	return collider;
}

void Cup::Update(float delta_)
{
	MoveSprite(spriteID, settings->GetFloat("CUP1_POSX"), settings->GetFloat("CUP1_POSY"));
}

void Cup::Draw()
{
	DrawSprite(spriteID);
}