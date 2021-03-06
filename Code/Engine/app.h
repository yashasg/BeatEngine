#pragma once
//==============================================================================
//  INCLUDES
//==============================================================================

#include <assert.h>

//==============================================================================
//  DEFINES
//==============================================================================

#undef ASSERT
#define ASSERT( _expr_ )  assert( _expr_ )

//==============================================================================
//  TYPES
//==============================================================================

class app
{
public:
            app     () { m_Quit = false; };
virtual	    ~app    () { };
virtual void Init   ( const char * pTitle , int Xpos , int Ypos ,
                      int Width , int Height , bool Fullscreen );
virtual void Kill   ();
virtual void Update  (float DeltaTime);
virtual void Render ();

        bool m_Quit;
};