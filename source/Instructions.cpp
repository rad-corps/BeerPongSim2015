#include "Instructions.h"
#include "GAMESTATE.h"
#include "AIE.h"


Instructions::Instructions(void)
{
	settings = FileSettings::Instance();
	stateSelection = GAME_STATES::INSTRUCTIONS;
	backgroundImage = CreateSprite("./images/instructions.png", settings->GetInt("SCREEN_W"), settings->GetInt("SCREEN_H"), true );
	MoveSprite( backgroundImage, settings->GetInt("SCREEN_W") * 0.5f, settings->GetInt("SCREEN_H") * 0.5f );
}


Instructions::~Instructions(void)
{
}

void Instructions::Draw()
{
	DrawSprite(backgroundImage);
}

void Instructions::Update()
{
	
}
