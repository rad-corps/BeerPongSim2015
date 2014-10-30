#pragma once
#include "gamestate.h"
#include "FileSettings.h"

class Instructions : public GAMESTATE
{
public:
	Instructions(void);
	~Instructions(void);

	virtual void Draw();
	virtual void Update();

private:
	FileSettings* settings;
};

