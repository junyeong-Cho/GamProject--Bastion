/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/


#include "Camera.h"

GAM200::Camera::Camera(Math::rect player_zone) :
    player_zone(player_zone), position({ 0, 0 })
{}

void GAM200::Camera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& GAM200::Camera::GetPosition() const
{
    return position;
}

void GAM200::Camera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

void GAM200::Camera::Update(const Math::vec2& player_position)
{
    if (player_position.x > player_zone.Right() + position.x)
    {
        position.x = player_position.x - player_zone.Right();
    }
    if (player_position.x - position.x < player_zone.Left())
    {
        position.x = player_position.x - player_zone.Left();
    }

    //카메라가 맵 범위 끝에 다다르면 이동을 멈추도록 하는 기능이다.
    if (position.x < limit.Left())
    {
        position.x = limit.Left();
    }
    if (position.x > limit.Right())
    {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom())
    {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top())
    {
        position.y = limit.Top();
    }
}

Math::TransformationMatrix GAM200::Camera::GetMatrix()
{
    return Math::TranslationMatrix(-position);
}



