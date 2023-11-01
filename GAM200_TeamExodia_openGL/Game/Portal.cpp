/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Portal.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "../Game/Portal.h"

#include "../Engine/Collision.h"


Portal::Portal(int to_state, Math::irect boundary) :
    GameObject(static_cast<Math::vec2>(boundary.point1)),
    to_state(to_state)
{
    AddGOComponent(new GAM200::RectCollision({ Math::ivec2{ 0, 0 }, boundary.Size() }, this));
}


void Portal::GoToState()
{
    Engine::GetGameStateManager().SetNextGameState(to_state);
}
