#pragma once

#include <cmath>
#include <utility>

class Vector2D
{
public:
    Vector2D() 
        : m_X(0.0f)
        , m_Y(0.0f) 
    {
    }

    Vector2D(float inX, float inY) 
        : m_X(inX)
        , m_Y(inY) 
    {
    }
    
    explicit Vector2D(const float& inValue) 
        : m_X(inValue)
        , m_Y(inValue) 
    {
    }

    Vector2D& operator+= (const Vector2D& inRhs)
    {
        m_X += inRhs.m_X;
        m_Y += inRhs.m_Y;
        return *this;
    }

    Vector2D& operator-= (const Vector2D& inRhs)
    {
        m_X -= inRhs.m_X;
        m_Y -= inRhs.m_Y;
        return *this;
    }

    Vector2D& operator*= (const Vector2D& inRhs)
    {
        m_X *= inRhs.m_X;
        m_Y *= inRhs.m_Y;
        return *this;
    }

    Vector2D& operator/= (const Vector2D& inRhs)
    {
        m_X /= inRhs.m_X;
        m_Y /= inRhs.m_Y;
        return *this;
    }

    auto Dot(const Vector2D& inRhs) const
    {
        return m_X * inRhs.m_X + m_Y * inRhs.m_Y;
    }

    auto Length() const
    {
        return sqrt(m_X * m_X + m_Y * m_Y);
    }

    void Normalize()
    {
        const float length = Length();
        m_X /= length;
        m_Y /= length;
    }

    Vector2D Normalized() const
    {
        const float length = Length();
        return Vector2D(m_X / length, m_Y / length);
    }

    void RotateDeg(float inAngleDegrees)
    {
        constexpr const float pi = 3.14159265358979323846f;
        const float radians = inAngleDegrees * (pi / 180.0f);
        m_X = m_X * cos(radians) + m_Y * sin(radians);
        m_Y = -m_X * sin(radians) + m_Y * cos(radians);
    }

    float m_X;
    float m_Y;
};

inline Vector2D operator+ (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X + inB.m_X, inA.m_Y + inB.m_Y);
}

inline Vector2D operator- (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X - inB.m_X, inA.m_Y - inB.m_Y);
}

inline Vector2D operator* (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X * inB.m_X, inA.m_Y * inB.m_Y);
}

inline Vector2D operator/ (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X / inB.m_X, inA.m_Y / inB.m_Y);
}

inline Vector2D operator+ (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue + inVector.m_X, inValue + inVector.m_Y);
}

inline Vector2D operator- (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue - inVector.m_X, inValue - inVector.m_Y);
}

inline Vector2D operator* (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue * inVector.m_X, inValue * inVector.m_Y);
}

inline Vector2D operator/ (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue / inVector.m_X, inValue / inVector.m_Y);
}

inline float Distance(const Vector2D& inA, const Vector2D& inB)
{
    return sqrt((inA.m_X - inB.m_X) * (inA.m_X - inB.m_X) + (inA.m_Y - inB.m_Y) * (inA.m_Y - inB.m_Y));
}
