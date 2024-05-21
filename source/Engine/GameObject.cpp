/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    November 1, 2023
*/

#include "ShowCollision.h"
#include "Collision.h"
#include "MergeCollision.h"
#include "GameObject.h"
#include "Matrix.h"

#include "Component/Map.h"

GAM200::GameObject::GameObject(Math::vec2 position) :
    GameObject(position, 0, { 1, 1 })
{ }

GAM200::GameObject::GameObject(Math::vec2 position, double rotation, Math::vec2 scale) :
    velocity({ 0,0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none),
    matrix_outdated(true),
    destroy(false)
{}

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

void GAM200::GameObject::Draw(Math::TransformationMatrix camera_matrix)
{
    Sprite* sprite = GetGOComponent<Sprite>();

    if (sprite != nullptr)
    {
        // camera matrix of CS230   : translation
        // camera matrix of current : translation + scale
        // object matrix            : translation + scale

        // this is previous code from CS230
        // it doesn't apply scaling of camera; scaling affects the translation of object
        // sprite->Draw(camera_matrix * GetMatrix());

        // this is the very current code
        // it should be fixed because object's matrix of scaling affects the camera matrix
        // sprite->Draw(GetMatrix() * camera_matrix);

        // So should use CS230 style but also calculate the camera's scale matrix
        /*Math::ScaleMatrix camera_scale(Math::vec2{ camera_matrix[0][0], camera_matrix[1][1] });
        Math::TranslationMatrix camera_translation(Math::vec2{ camera_matrix[0][2], camera_matrix[1][2] });
        sprite->Draw(camera_translation * GetMatrix() * camera_scale);*/

        // This doesn't work either. Found the problem. What is the issue?
        // Somehow the code runs as written. However, the problem is,
        // when applying the camera matrix's scale (zoom in & out), distant objects should appear farther away, but
        // in the current code, it just scales everything, making all objects just increase or decrease in size. In other words,
        // it doesn't feel like zooming in or out; it just scales all objects at their positions.
        // Therefore, the above code scales the object and then applies s, r, t, and camera translation,
        // which means the object translation is not affected by the camera scale.
        // Using the previous code applies the camera scale to the object translation based on the origin, causing issues.
        // So, let's do additional calculations based on the camera's translate position for object translation,
        // then scale and translate again.
        Math::ScaleMatrix       camera_scale(Math::vec2{ camera_matrix[0][0], camera_matrix[1][1] });
        Math::vec2              camera_position(Math::vec2(camera_matrix[0][2], camera_matrix[1][2]));
        Math::TranslationMatrix camera_translation(camera_position);

        Math::ScaleMatrix       object_scale(scale);
        Math::RotationMatrix    object_rotate(rotation);
        Math::TranslationMatrix object_translate(position);

        Math::TranslationMatrix centered_translation(Math::vec2{ position.x - camera_matrix[0][2], position.y - camera_matrix[1][2]});

        sprite->Draw(camera_translation * camera_scale * centered_translation * object_rotate * object_scale);
    }


    ShowCollision* show_collision = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();

    if (show_collision != nullptr && show_collision->Enabled())
    {
        if (GetGOComponent<Collision>() != nullptr)
        {
            GetGOComponent<Collision>()->Draw(camera_matrix);
        }
    }
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


bool GAM200::GameObject::IsMergingWith(GameObject* other_object)
{
    MergeCollision* collider = GetGOComponent<MergeCollision>();

    return collider != nullptr && collider->IsMergingWith(other_object);
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

bool GAM200::GameObject::CanMergeWith(GameObjectTypes other_object_type)
{
    return false;
}

const Math::TransformationMatrix& GAM200::GameObject::GetMatrix()
{
    if (matrix_outdated)
    {
        object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
        // object_matrix = Math::TranslationMatrix(position);
        matrix_outdated = false;
    }
    return object_matrix;
}

const Math::vec2& GAM200::GameObject::GetPosition() const
{
    return position;
}

const Math::vec2& GAM200::GameObject::GetVelocity() const
{
    return velocity;
}

const Math::vec2& GAM200::GameObject::GetScale() const
{
    return scale;
}

double GAM200::GameObject::GetRotation() const
{
    return rotation;
}

double GAM200::GameObject::GetSquareDistance(GameObject* obj) {
    return (position.x - obj->GetPosition().x) * (position.x - obj->GetPosition().x) + (position.y - obj->GetPosition().y) * (position.y - obj->GetPosition().y);
}

void GAM200::GameObject::change_state(State* new_state)
{
    current_state = new_state;
    current_state->Enter(this);
}

void GAM200::GameObject::SetPosition(Math::vec2 new_position)
{
    position = new_position;
    matrix_outdated = true;
}

void GAM200::GameObject::UpdatePosition(Math::vec2 delta)
{
    position += delta;
    matrix_outdated = true;
}


void GAM200::GameObject::SetVelocity(Math::vec2 new_position)
{
    velocity = new_position;
    matrix_outdated = true;
}

void GAM200::GameObject::UpdateVelocity(Math::vec2 delta)
{
    velocity += delta;
    matrix_outdated = true;
}

void GAM200::GameObject::SetScale(Math::vec2 new_scale)
{
    scale = new_scale;
    matrix_outdated = true;
}

void GAM200::GameObject::UpdateScale(Math::vec2 delta)
{
    scale += delta;
    matrix_outdated = true;
}


void GAM200::GameObject::SetRotation(double new_rotation)
{
    rotation = new_rotation;
    matrix_outdated = true;
}

void GAM200::GameObject::UpdateRotation(double delta)
{
    rotation += delta;
    matrix_outdated = true;
}


