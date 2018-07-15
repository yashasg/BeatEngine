#pragma once
#include "../Engine/app.h"
class Game:public app
{
virtual void Init   ( const char * pTitle , int Xpos , int Ypos ,
                       int Width , int Height , bool Fullscreen )                                         override;
virtual	void Kill   ( )                      override;
virtual	void Update ( float DeltaTime )      override;
virtual	void Render ( )                      override;
};