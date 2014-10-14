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

	Rect GetCollider();

private:
	unsigned int spriteID;
	FileSettings *settings;

	Rect collider;
};

