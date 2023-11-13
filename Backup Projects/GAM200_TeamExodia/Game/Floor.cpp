/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/


#include "../Game/Floor.h"

#include "../Engine/Rect.h"
#include "../Engine/Collision.h"


Floor::Floor(Math::irect boundary) : GameObject(static_cast<Math::vec2>(boundary.point1)) 
{
    AddGOComponent(new CS230::RectCollision({ Math::ivec2{ 0, 0 }, boundary.Size() }, this));
}
