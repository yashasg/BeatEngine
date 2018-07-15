#pragma once

struct SDL_Window;
struct SDL_Renderer;

class graphics
{
public:
        graphics    ();
        ~graphics   ();
void    Init        ( SDL_Window* pWindow);
void    Render      ();
void    Kill        ();

private:
SDL_Renderer*   m_pRenderer;
};
