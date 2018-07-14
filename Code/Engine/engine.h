//==============================================================================
//  INCLUDES
//==============================================================================

#include "app.h"
#include <assert.h>
#include <stdint.h>

//==============================================================================
//  DEFINES
//==============================================================================

#undef ASSERT
#define ASSERT( _expr_ )  assert( _expr_ )

//==============================================================================
//  TYPES
//==============================================================================

class engine
{
public:
                        engine( void );
virtual                 ~engine( void );

virtual void            Exit( int       ExitCode ); // Exit application.

virtual int             sprintf( char*         buffer ,
                             size_t        sizeOfBuffer ,
                             const char*   format ,
                             ... );                // Platform safe sprintf.

virtual uint32_t        GetAppTime( void );        // Get the application time.
virtual uint32_t        GetRealTime( void );       // Get real time.

virtual bool            IsKeyPressed( int       Key );// Check if a key is pressed.

};

//==============================================================================
//  STORAGE
//==============================================================================

extern engine* Engine;

//==============================================================================
//------------------------------------------------------------------------------
//
// entry point definition.
//

#define TINY_ENGINE_MAIN( App, Title,Xpos, Ypos, Width, Height, Fullscreen )\
                                                                            \
    {                                                                       \
        return TinyEngineMain( App,                                         \
                               Title,                                       \
                               Xpos,                                        \
                               Ypos,                                        \
                               Width,                                       \
                               Height,                                      \
                               Fullscreen );                                \
    }                                                                       \

int TinyEngineMain( app* App,const char * pTitle , int Xpos , int Ypos , int Width , int Height , bool Fullscreen );

//------------------------------------------------------------------------------