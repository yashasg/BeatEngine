//==============================================================================
//  INCLUDES
//==============================================================================

#include "Game.h"
#include "../Engine/engine.h"

//==============================================================================
//  DEFINES
//==============================================================================

#define WINDOW_CENTERED 0

//==============================================================================
//  STORAGE
//==============================================================================

Game s_Game;

//==============================================================================
//  FUNCTIONS - main
//==============================================================================

int main(int argc, char *argv[])
{
    const char* Title="2DDemo";
    TINY_ENGINE_MAIN( &s_Game, Title , 800 , 600 , false);
	
	return 0;
}

//==============================================================================