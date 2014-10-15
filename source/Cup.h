#pragma once

#include "FileSettings.h"
#include "Rect.h"

class Cup
{
public:
	Cup(void);
	~Cup(void);

	void Draw();
	void Update(float delta_);

	Rect GetCupCollider();
	Rect GetRimCollider();

private:
	unsigned int spriteID;
	FileSettings *settings;

	Rect cupCollider;
	Rect rimCollider;
	Vector2 cupPos;
	Vector2 rimPos;
};

