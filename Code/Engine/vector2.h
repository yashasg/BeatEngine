#pragma once

struct vector2
{
        float m_X;
        float m_Y;
public:
        vector2     ( ) :m_X(0), m_Y(0) { };
        vector2     ( float X, float Y ) :m_X(X), m_Y(Y) { };
        vector2     ( vector2& RHS ) :m_X(RHS.m_X), m_Y(RHS.m_Y) { };
        ~vector2    ( ) { };

};