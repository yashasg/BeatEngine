#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "DejaLib.h"
#include "obj_mgr.h"

void Game::Init()
{
    DEJA_CONTEXT( "beat_game::Init" );
    DEJA_APP_LABEL( "beat_game" );
}

void Game::Update(float DeltaTime)
{
    SDL_Event Event;
    SDL_PollEvent( &Event );
    switch ( Event.type )
    {
        case SDL_QUIT:
            m_Quit = true;
            break;
        default:
            break;
    }
}

void Game::Render()
{
}

void Game::Kill()
{

}
