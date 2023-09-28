/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Vec2.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#include "../Engine/Vec2.h"

//Vec2
bool Math::vec2::operator==(const vec2& v)
{
    if (x == v.x && y == v.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Math::vec2::operator!=(const vec2& v)
{
    if (x != v.x && y != v.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}


Math::vec2 Math::vec2::operator+(const vec2& v)
{
    return { x + v.x, y + v.y };
}

Math::vec2& Math::vec2::operator+=(const vec2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}


Math::vec2 Math::vec2::operator-(const vec2& v)
{
    return { x - v.x, y - v.y };
}

Math::vec2& Math::vec2::operator-=(const vec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}


Math::vec2 Math::vec2::operator*(double scale)
{
    return { x * scale, y * scale };
}

Math::vec2& Math::vec2::operator*=(double scale)
{
    x *= scale;
    y *= scale;
    return *this;
}


Math::vec2 Math::vec2::operator/(double divisor)
{
    return { x / divisor, y / divisor };
}

Math::vec2& Math::vec2::operator/=(double divisor)
{
    x /= divisor;
    y /= divisor;
    return *this;
}

Math::vec2 Math::vec2::operator-()
{
    return { (double)-x,(double)-y };
}

void Math::vec2::Normalize()
{
    double magnitude = sqrt(x * x + y * y);

    if (magnitude > 0.0)
    {
        x /= magnitude;
        y /= magnitude;
    }
}


Math::vec2 Math::operator*(double scale, const vec2& v)
{
    return { scale * v.x, scale * v.y };
}



//ivec2
bool Math::ivec2::operator==(const ivec2& v)
{
    if (x == v.x && y == v.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Math::ivec2::operator!=(const ivec2& v) {
    if (x != v.x && y != v.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}


Math::ivec2 Math::ivec2::operator+(const ivec2& v)
{
    return { x + v.x, y + v.y };
}

Math::ivec2& Math::ivec2::operator+=(const ivec2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}


Math::ivec2 Math::ivec2::operator-(const ivec2& v)
{
    return { x - v.x, y - v.y };
}

Math::ivec2& Math::ivec2::operator-=(const ivec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}


Math::ivec2 Math::ivec2::operator*(int scale)
{
    return { x * scale, y * scale };
}

Math::ivec2& Math::ivec2::operator*=(int scale)
{
    x *= scale;
    y *= scale;
    return *this;
}


Math::ivec2 Math::ivec2::operator/(int divisor)
{
    return { x / divisor, y / divisor };
}

Math::ivec2& Math::ivec2::operator/=(int divisor)
{
    x /= divisor;
    y /= divisor;
    return *this;
}

Math::vec2 Math::ivec2::operator/(double divisor)
{
    return { x / divisor, y / divisor };
}




Math::vec2 Math::ivec2::operator*(double scale)
{
    return { x * scale, y / scale };
}


Math::vec2 Math::ivec2::operator-()
{
    return { (double)-x, (double)-y };
}