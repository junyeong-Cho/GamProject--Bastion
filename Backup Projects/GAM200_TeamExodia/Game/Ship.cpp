/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/Engine.h"

#include "../Engine/ShowCollision.h"
#include "ScreenWrap.h"
#include "Ship.h"


Ship::Ship(Math::vec2 start_position) :
    GameObject(start_position, 0, { scale, scale }), flame_left("Assets/Flame.spt", (this)), flame_right("Assets/Flame.spt", (this))
{
    AddGOComponent(new ScreenWrap(*this));
    AddGOComponent(new CS230::Sprite("Assets/Ship.spt", (this)));

    exploded = false;

    flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));
    flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
}


void Ship::Update(double dt) 
{
    UpdateGOComponents(dt);
    GetGOComponent<CS230::Sprite>()->Update(dt);
    flame_left.Update(dt);
    flame_right.Update(dt);

    if (!exploded)
    {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::W))
        {
            UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, speed * dt });

            if (is_thrusting == false)
            {
                flame_left.PlayAnimation(static_cast<int>(Flame_Animations::Flame));
                flame_right.PlayAnimation(static_cast<int>(Flame_Animations::Flame));
                is_thrusting = true;
            }
        }
        else
        {
            if (is_thrusting == true)
            {
                flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
                flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));
                is_thrusting = false;
            }
        }

        if (Engine::GetInput().KeyDown(CS230::Input::Keys::A))
        {
            UpdateRotation(rotation_speed * dt);
        }
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::D))
        {
            UpdateRotation(-(rotation_speed * dt));
        }

        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(3)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(4)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
        }
    }
    


    if (exploded && GetGOComponent<CS230::Sprite>()->AnimationEnded() && !is_idle)
    {
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
        flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
        flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));

        is_idle = true;
    }

    UpdateVelocity(-(dt * drag * GetVelocity()));
    UpdatePosition(dt * GetVelocity());



}


void Ship::ResolveCollision(GameObject* other_object)
{

    switch (other_object->Type())
    {
    case GameObjectTypes::Meteor:
        if (GetGOComponent<CS230::Sprite>() != nullptr) // Check if the Sprite component exists
        {
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Explosion));


            exploded = true;

            RemoveGOComponent<CS230::Collision>();
        }

        break;

    default:

        break;
    }

}


bool Ship::CanCollideWith(GameObjectTypes)
{
    return true;
}



bool Ship::Exploded()
{
    return exploded;
}

void Ship::Draw( Math::TransformationMatrix camera_matrix)
{
    if (!exploded)
    {
        flame_left.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
        flame_right.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
    }
    
    if (!exploded || !is_idle)
    {
        GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
    }


    CS230::ShowCollision* showcollision = Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>();
    if (showcollision != nullptr && showcollision->Enabled())
    {
        CS230::Collision* collision = GetGOComponent<CS230::Collision>();
        if (collision != nullptr)
        {
            collision->Draw(camera_matrix);
        }

    }
}