#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#if !defined(OSX)
#include <crtdbg.h>
#endif
#include <iostream>
#include <list>

#include "BeerPongGame.h"

//this will only work in a Windows environment
#include "FileSettings.h"

int main( int argc, char* argv[] )
{	
	srand (time(NULL));
	FileSettings* fs = FileSettings::Instance();
	BeerPongGame game;
	game.Run();
		
	Shutdown();

	return 0;
}
