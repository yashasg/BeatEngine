//==============================================================================
//  INCLUDES
//==============================================================================
#include "app.h"
#include "SDL.h"
#include "DejaLib.h"
#include "graphics.h"
//==============================================================================
//  STORAGE
//==============================================================================

graphics*       s_pGraphics;      //pointer to the graphics engine
SDL_Window*     s_pWindow;      //window render the application

//==============================================================================
// app
//==============================================================================

void app::Init( const char * pTitle , int Xpos , int Ypos , int Width ,
                int Height , bool Fullscreen )
{
    int Flags =0;
    if ( Fullscreen )
    {
        Flags = SDL_WINDOW_FULLSCREEN;
    }
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
        DEJA_CONTEXT( "SDL Initialized!..." );
        s_pWindow=SDL_CreateWindow( pTitle , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , Width , Height , Flags );
        if ( s_pWindow )
        {
            DEJA_CONTEXT( "Window Created!..." );
            s_pGraphics = new graphics;
            s_pGraphics->Init( s_pWindow );
        }
        else
        {
            DEJA_CONTEXT( "Unable to Create window!..." );
            m_Quit = true;
        }

     }
    else
     {
        DEJA_CONTEXT( "Unable to Initialize SDL" );
        m_Quit=true;
     }
}

//==============================================================================

void app::Kill( )
{
    s_pGraphics->Kill();
    delete s_pGraphics;
    s_pGraphics=NULL;

    SDL_DestroyWindow( s_pWindow );
    SDL_Quit( );
}

//==============================================================================

void app::Update(float DeltaTime)
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

//==============================================================================

void app::Render()
{
      s_pGraphics->Render();
}

//==============================================================================