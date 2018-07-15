//==============================================================================
//  INCLUDES
//==============================================================================

#include "app.h"
#include <stdint.h>

//==============================================================================
//  DEFINES
//==============================================================================

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

#define TINY_ENGINE_MAIN( App, Title, Width, Height, Fullscreen )\
                                                                            \
    {                                                                       \
        return TinyEngineMain( App,                                         \
                               Title,                                       \
                               Width,                                       \
                               Height,                                      \
                               Fullscreen );                                \
    }                                                                       \

int TinyEngineMain( app* App,const char * pTitle , int Width , int Height , bool Fullscreen );

//------------------------------------------------------------------------------