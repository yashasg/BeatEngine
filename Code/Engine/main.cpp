#include "Game.h"
#include "SDL.h"
#include "engine.h"
#define FPS 60;
Game s_Game;
int main(int argc, char *argv[])
{
    const char* Title="BeatEngine";
    TINY_ENGINE_MAIN( &s_Game, Title , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 600 , false);

	//Game* pGame = new Game;
	//pGame->Init("BeatEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	//while (pGame->IsRunning())
	//{
	//	const uint32_t FrameDelay = 1000 / FPS;
	//	const uint32_t FrameStart = SDL_GetTicks();
	//	pGame->Update();
	//	pGame->Render();
	//	const uint32_t FrameTime = SDL_GetTicks()- FrameStart;

	//	if (FrameDelay > FrameTime)
	//	{
	//		SDL_Delay(FrameDelay - FrameTime);
	//	}
	//}
	//pGame->Clean();
	
	return 0;
}