#pragma once

#include "FileSettings.h"
#include "Rect.h"
#include "Vector.h"

struct CupInitialiser
{
	Vector2 pos;
	float width;
	float height;
	int victim;
};

class Cup
{
public:
	Cup(void);
	Cup(CupInitialiser ci_);
	~Cup(void);

	void Draw();
	void Update(float delta_);

	Rect GetCupCollider();
	Rect GetRimCollider();

	//who takes a drink if this cup gets a pong in it?
	int victim;

private:
	unsigned int spriteID;
	FileSettings *settings;

	Rect cupCollider;
	Rect rimCollider;
	Vector2 cupPos;
	Vector2 rimPos;

	
};

