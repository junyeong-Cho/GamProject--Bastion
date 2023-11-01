/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Mode1.h"
#include "Asteroid.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"



Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position)
{
    AddGOComponent(new GAM200::Sprite("Assets/Asteroid.spt", (this)));
    current_state = &state_bouncing;
    current_state->Enter(this);
}


bool Asteroid::CanCollideWith(GameObjectTypes type)
{
    return type == GameObjectTypes::Floor;
}


void Asteroid::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Floor)
    {
        SetPosition({ GetPosition().x, other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary().Top() + 1 }); //Added extra pixel of height
        SetVelocity({ GetVelocity().x, 0 });
        current_state = &state_landing;
        current_state->Enter(this);
    }
    //GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::AsteroidLand));

}



//old ver of Asteroid::Draw
/*
void Asteroid::Draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Draw(camera_matrix * object_matrix);
}
*/



//Bouncing finite


void Asteroid::State_Bouncing::Enter(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));

    asteroid->SetVelocity({ asteroid->GetVelocity().x, bounce_velocity });
}

void Asteroid::State_Bouncing::Update(GameObject* object, double dt)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->SetVelocity({ asteroid->GetVelocity().x, asteroid->GetVelocity().y - Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
}

void Asteroid::State_Bouncing::CheckExit(GameObject* object)
{
    //Old logic of State_Bouncing::CheckExit

    /*
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));

    if (asteroid->GetPosition().y < Mode1::floor)
    {
        asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
        asteroid->SetVelocity({ 0, 0 });
        asteroid->change_state(&asteroid->state_landing);
    }
    */
}



//Old ver of State_Bouncing::CheckExit
/*
void Asteroid::State_Bouncing::CheckExit(Asteroid* asteroid)
{
    asteroid->sprite.PlayAnimation(static_cast<int>(Animations::Landing));

    if (asteroid->position.y <= Mode1::floor)
    {
        asteroid->change_state(&asteroid->state_landing);
    }
}
*/



void Asteroid::State_Landing::Enter(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    asteroid->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::AsteroidLand));


    asteroid->SetVelocity({ asteroid->GetVelocity().x, 0 });
    asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });

}

void Asteroid::State_Landing::Update(GameObject* object, double dt)
{

}

void Asteroid::State_Landing::CheckExit(GameObject* object)
{
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    if (asteroid->GetGOComponent<GAM200::Sprite>()->AnimationEnded())
    {
        asteroid->change_state(&asteroid->state_bouncing);
    }
}


