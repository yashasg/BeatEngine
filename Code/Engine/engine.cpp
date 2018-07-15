//==============================================================================
//  INCLUDES
//==============================================================================

#include "engine.h"
#include "DejaLib.h"
#include "SDL.h"

//==============================================================================
//  LIBS
//==============================================================================

//==============================================================================
//  DEFINES
//==============================================================================

#define FPS_LIMIT       60
//==============================================================================
//  STORAGE
//==============================================================================

        app*            g_TheApp;

        engine*         Engine = NULL;                        // The Engine.
        uint32_t        s_AppTime=0;
        SDL_Renderer*   m_pRenderer;
//==============================================================================
// TinyEngineMain
//==============================================================================

int TinyEngineMain( app* App, const char * pTitle , 
                    int Width,int Height , bool Fullscreen )
{
    DEJA_CONTEXT( "TinyEngineMain" );
    ASSERT(App);
    g_TheApp=App;
    // Create subsystems.
    Engine = ( engine* )new engine;
    int WindowPos= SDL_WINDOWPOS_CENTERED;
    // Call application initialization.
    g_TheApp->Init( pTitle , WindowPos , WindowPos , Width , Height ,                           Fullscreen );
    //    /*SDL_Surface* pSurface = IMG_Load( "../../../../Assets/testsprite.png" );
    //    s_pEnemy = SDL_CreateTextureFromSurface( m_pRenderer , pSurface );
    //    SDL_FreeSurface( pSurface );*/
    //    g_TheApp->m_Quit = false;
    //}

    //** By forcing a flush, we trigger the DejaLib to go ahead and connect with
    //** Insight.  You wouldn't normally do this, but, since the connection
    //** process takes a moment, it was causing a framerate hitch.  Applications
    //** which have a non-trivial start up phase (unlike most demos using the
    //** TinyEngine) will likely generate enough DejaLib traffic so as to
    //** automatically connect before the main render loop.
    DEJA_FLUSH( );

    // Main loop.
    uint32_t RealStart = Engine->GetRealTime( );
    while ( !g_TheApp->m_Quit )
    {
        // Determine the delta time using "real" time.
        uint32_t NewRealStart = Engine->GetRealTime( );
        uint32_t DeltaTime = NewRealStart - RealStart;
        uint32_t FrameTime = 1000 / FPS_LIMIT;
        RealStart = NewRealStart;

        // If the delta time is too large, then we want to constrain it.
        // This prevents huge delta time values when the app is hung up on
        // a break point or is being dragged.
        if ( DeltaTime > FrameTime  )
        {
            DeltaTime = FrameTime;
        }

        // Advance the application time.
        s_AppTime += DeltaTime;

        // Update.
        g_TheApp->Update( ((float)DeltaTime)/1000.0f );

        // Render.
        g_TheApp->Render();
        
        // Cap frame rate
        uint32_t DelayMS= FrameTime - DeltaTime;
        SDL_Delay( DelayMS );
    }

    g_TheApp->Kill( );
    

    delete Engine;
    Engine = NULL;
    return 0;
}

//==============================================================================
// engine
//==============================================================================

engine::engine( void )
{

}

//==============================================================================
// ~engine
//==============================================================================

engine::~engine( void )
{
}

//==============================================================================
// Exit
//==============================================================================

void engine::Exit( int ExitCode )
{
    (void) ExitCode;
    g_TheApp->m_Quit=true;
}

//==============================================================================
// sprintf
//==============================================================================

int engine::sprintf( char*        buffer ,
                     size_t       sizeOfBuffer ,
                     const char*  format ,
                     ... )
{
    va_list args;
    va_start( args , format );

    int Count = vsprintf_s( buffer , sizeOfBuffer , format , args );

    return Count;
}

//==============================================================================
// GetAppTime
//==============================================================================

uint32_t engine::GetAppTime( void )
{
    return( s_AppTime );
}

//==============================================================================
// GetRealTime
//==============================================================================

uint32_t engine::GetRealTime( void )
{
    return SDL_GetTicks( );
}

//==============================================================================
// IsKeyPressed
//==============================================================================

bool engine::IsKeyPressed( int Key )
{
        return( false );
}

//==============================================================================
