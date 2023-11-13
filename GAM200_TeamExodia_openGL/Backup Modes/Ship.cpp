/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    November 2, 2023
*/

#pragma once

#include "../Engine/Engine.h"

#include "../Engine/ShowCollision.h"
#include "ScreenWrap.h"
#include "Ship.h"


Ship::Ship(Math::vec2 start_position) :
    GameObject(start_position, 0, { scale, scale }), flame_left("assets/Flame.spt", (this)), flame_right("assets/Flame.spt", (this))
{
    AddGOComponent(new ScreenWrap(*this));
    AddGOComponent(new GAM200::Sprite("assets/Ship.spt", (this)));

    exploded = false;

    flame_right.PlayAnimation(static_cast<int>(Flame_Animations::None));
    flame_left.PlayAnimation(static_cast<int>(Flame_Animations::None));
}


void Ship::Update(double dt)
{
    UpdateGOComponents(dt);
    GetGOComponent<GAM200::Sprite>()->Update(dt);
    flame_left.Update(dt);
    flame_right.Update(dt);

    if (!exploded)
    {
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::W))
        {
            UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, speed* dt });

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

        if (Engine::GetInput().keyDown(GAM200::Input::Keys::A))
        {
            UpdateRotation(rotation_speed * dt);
        }
        if (Engine::GetInput().keyDown(GAM200::Input::Keys::D))
        {
            UpdateRotation(-(rotation_speed * dt));
        }

        if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter)) 
        {
            Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<GAM200::Sprite>()->GetHotSpot(3)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
            Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(
                new Laser(
                    GetMatrix() * Math::vec2(GetGOComponent<GAM200::Sprite>()->GetHotSpot(4)),
                    GetRotation(),
                    GetScale(),
                    Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, Laser::DefaultVelocity }));
        }
    }



    if (exploded && GetGOComponent<GAM200::Sprite>()->AnimationEnded() && !is_idle)
    {
        GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
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
        if (GetGOComponent<GAM200::Sprite>() != nullptr) // Check if the Sprite component exists
        {
            GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Explosion));


            exploded = true;

            RemoveGOComponent<GAM200::Collision>();
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

void Ship::Draw(Math::TransformationMatrix camera_matrix)
{
    if (!exploded)
    {
        flame_left.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(1)));
        flame_right.Draw(GetMatrix() * Math::TranslationMatrix(GetGOComponent<GAM200::Sprite>()->GetHotSpot(2)));
    }

    if (!exploded || !is_idle)
    {
        GetGOComponent<GAM200::Sprite>()->Draw(GetMatrix());
    }


    GAM200::ShowCollision* showcollision = Engine::GetGameStateManager().GetGSComponent<GAM200::ShowCollision>();
    if (showcollision != nullptr && showcollision->Enabled())
    {
        GAM200::Collision* collision = GetGOComponent<GAM200::Collision>();
        if (collision != nullptr)
        {
            collision->Draw(camera_matrix);
        }

    }
}