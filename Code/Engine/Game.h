#pragma once
#include "app.h"
class Game:public app
{
    virtual void Init( )                     override;
    virtual	void Kill( )                     override;
    virtual	void Update( float DeltaTime )   override;
    virtual	void Render( )                   override;
};