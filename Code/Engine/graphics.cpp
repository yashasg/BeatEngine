#include "graphics.h"
#include "app.h"    //just for ASSERT
#include "DejaLib.h"
#include "SDL.h"
graphics::graphics( )
{
}

graphics::~graphics( )
{
}

void graphics::Init( SDL_Window* pWindow )
{
    ASSERT(pWindow);
    m_pRenderer = SDL_CreateRenderer( pWindow , -1 , 0 );
    ASSERT (m_pRenderer );
    DEJA_CONTEXT( "Renderer Created!..." );
    //set a default color so we know its working
    SDL_SetRenderDrawColor( m_pRenderer , 244 , 150 , 10 , 255 );
}

void graphics::Render( )
{
    SDL_RenderClear( m_pRenderer );
    //do stuff
    //SDL_RenderCopy( m_pRenderer , s_pEnemy , NULL , &s_pEnemyRect );
    SDL_RenderPresent( m_pRenderer );
}

void graphics::Kill( )
{
    SDL_DestroyRenderer( m_pRenderer );
}
