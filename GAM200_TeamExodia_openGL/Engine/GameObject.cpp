/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    GAM200 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#include "ShowCollision.h"
#include "Collision.h"
#include "GameObject.h"
#include "Matrix.h"


GAM200::GameObject::GameObject(Math::vec2 position) :position(position) { }

void GAM200::GameObject::Update(double dt)
{
    current_state->Update(this, dt);

    if (velocity.x != 0 || velocity.y != 0)
    {
        UpdatePosition(velocity * dt);
    }

    UpdateGOComponents(dt);
    current_state->CheckExit(this);
}

void GAM200::GameObject::Draw(Math::vec2 position)
{
    /*Sprite* sprite = GetGOComponent<Sprite>();

    if (sprite != nullptr)
    {
        sprite->Draw(camera_matrix * GetMatrix());
    }

    ShowCollision* show_collision = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();

    if (show_collision != nullptr && show_collision->Enabled())
    {
        if (GetGOComponent<Collision>() != nullptr)
        {
            GetGOComponent<Collision>()->Draw(camera_matrix);
        }
    }*/
}


bool GAM200::GameObject::IsCollidingWith(Math::vec2 point)
{
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(point);
}




bool GAM200::GameObject::IsCollidingWith(GameObject* other_object)
{
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(other_object);
}


void GAM200::GameObject::Destroy()
{
    destroy = true;
}

bool GAM200::GameObject::Destroyed()
{
    return destroy;
}



bool GAM200::GameObject::CanCollideWith(GameObjectTypes other_object_type)
{
    return false;
}


const Math::vec2& GAM200::GameObject::GetPosition() const
{
    return position;
}

const Math::vec2& GAM200::GameObject::GetVelocity() const
{
    return velocity;
}


void GAM200::GameObject::change_state(State* new_state)
{
    current_state = new_state;
    current_state->Enter(this);
}

void GAM200::GameObject::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

void GAM200::GameObject::UpdatePosition(Math::vec2 delta)
{
    position += delta;
}


void GAM200::GameObject::SetVelocity(Math::vec2 new_position)
{
    velocity = new_position;
}

void GAM200::GameObject::UpdateVelocity(Math::vec2 delta)
{
    velocity += delta;
}
