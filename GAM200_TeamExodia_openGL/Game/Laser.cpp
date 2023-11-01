/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Laser.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Laser.h"


Laser::Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel)
    : GameObject(pos, rot, scale)
{
    SetVelocity(vel);
    AddGOComponent(new GAM200::Sprite("Assets/Laser.spt", (this)));
}

void Laser::Update(double dt)
{
    GameObject::Update(dt);

    // Check if the laser is outside of the window
    Math::ivec2 frame_size = GetGOComponent<GAM200::Sprite>()->GetFrameSize();
    if (GetPosition().x < -frame_size.x || GetPosition().x > 800 + frame_size.x ||
        GetPosition().y < -frame_size.y || GetPosition().y > 600 + frame_size.y)
    {
        Destroy();
    }
}

bool Laser::CanCollideWith(GameObjectTypes other_object_type)
{
    return other_object_type == GameObjectTypes::Meteor;
}

void Laser::ResolveCollision(GameObject* other_object)
{
    Destroy();
    other_object->ResolveCollision(this);
}
