#pragma once
class app
{
public:
            app     () { m_Quit = false; };
virtual	    ~app    () { };
virtual void Init   () { };
virtual	void Kill   () { };
virtual	void Update  (float DeltaTime);
virtual	void Render ();

        bool m_Quit;
};