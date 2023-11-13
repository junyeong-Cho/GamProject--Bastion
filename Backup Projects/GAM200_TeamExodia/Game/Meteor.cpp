/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#include "../Engine/Engine.h"
#include "../Engine/Window.h"
#include "../Engine/Constants.h"


#include "Meteor.h"
#include "../Engine/Particle.h"
#include "Particles.h"


Meteor::Meteor() : Meteor(nullptr) {}

/*

Meteor::Meteor(Math::vec2 position) : CS230::GameObject(position)
{
    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", (this)));

    SetVelocity({ (rand() % (int)(default_velocity * 2)) - default_velocity , (rand() % (int)(default_velocity * 2)) - default_velocity });

    SetRotation((rand() % 360) * PI / 180);

    SetPosition({ static_cast<double>((rand() % (int)(Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x)) + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2),
                  static_cast<double>((rand() % (int)(Engine::GetWindow().GetSize().y - GetGOComponent<CS230::Sprite>()->GetFrameSize().y)) + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2) });

}
*/


Meteor::Meteor(Meteor* parent) : CS230::GameObject({ 0, 0 })
{
    AddGOComponent(new CS230::Sprite("Assets/Meteor.spt", this));

    if (parent == nullptr)
    {
        SetVelocity(Math::vec2
            {
                ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity,
                ((double)rand() / RAND_MAX) * default_velocity * 2 - default_velocity
            });

        int boundary = GetGOComponent<CS230::Sprite>()->GetFrameSize().x; // Assuming x and y size are the same

        // Choose a random boundary (top, bottom, left, right)
        int randBoundary = rand() % 4;

        double xPos, yPos;

        switch (randBoundary)
        {
        case 0: // Top boundary
            xPos = ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().x;
            yPos = -boundary;
            break;

        case 1: // Bottom boundary
            xPos = ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().x;
            yPos = Engine::GetWindow().GetSize().y + boundary;
            break;

        case 2: // Left boundary
            xPos = -boundary;
            yPos = ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().y;
            break;

        case 3: // Right boundary
            xPos = Engine::GetWindow().GetSize().x + boundary;
            yPos = ((double)rand() / RAND_MAX) * Engine::GetWindow().GetSize().y;
            break;
        }
        SetPosition({ xPos, yPos });

        SetRotation(((double)rand() / RAND_MAX) * 2 * (Math::PI));

        size = default_size;
    }
    else
    {
        SetVelocity(parent->GetVelocity());
        SetPosition(parent->GetPosition());
        SetRotation(parent->GetRotation());

        size = parent->size - 1;
    }

    health = default_healths[size];
    SetScale(Math::vec2{ default_scales[size], default_scales[size] });
}




void Meteor::ResolveCollision(GameObject* other_object) 
{
    switch (other_object->Type())
    {   
    case GameObjectTypes::Laser:

        Math::vec2 collisionPoint    = other_object->GetPosition();
        Math::vec2 vectorToCollision = collisionPoint - GetPosition();

        vectorToCollision.Normalize();

        Math::vec2 particlePosition = GetPosition();

        particlePosition.x += vectorToCollision.x * GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2;
        particlePosition.y += vectorToCollision.y * GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2;


        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Hit>>()->Emit(1, particlePosition, { 0, 0 }, { 0, 100 }, Math::PI / 2);
        Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::MeteorBit>>()->Emit(5, particlePosition, { 0, 0 }, { 0, 100 }, Math::PI / 3);

    }


    UpdateVelocity(0.01 * other_object->GetVelocity());

    health -= 1;

    if (health < 0) 
    {
        RemoveGOComponent<CS230::Collision>();
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Fade));
        //auto radius = GetGOComponent<CS230::CircleCollision>()->GetRadius();
        if (size > 0) 
        {

            Score* score = Engine::GetGameStateManager().GetGSComponent<Score>();
            score->Add(10);

            Meteor* meteor_1 = new Meteor(this);
            meteor_1->SetVelocity(Math::RotationMatrix((Math::PI) / 6) * GetVelocity());
           // GetGOComponent<CS230::CircleCollision>()->Draw(Math::ScaleMatrix(1.0 / default_scales[size]));
            

            Meteor* meteor_2 = new Meteor(this);
            meteor_2->SetVelocity(Math::RotationMatrix(-(Math::PI) / 6) * GetVelocity());
           // GetGOComponent<CS230::CircleCollision>()->Draw(Math::ScaleMatrix(1.0 / default_scales[size]));


            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_1);
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(meteor_2);
        }
    }
}



void Meteor::Update(double dt)
{
	//allow the meteor to move as well by calling the appropriate base class function , along with checking for wrapping around the screen.
    GameObject::Update(dt);

    // In Meteor::Update(), check if the Meteor::Animations::Fade is the current animation and also check if the animation has ended. If it has, then call Destroy().
    if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Fade) && GetGOComponent<CS230::Sprite>()->AnimationEnded())
    {
		Destroy();
	}
    
    if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / static_cast<double>(2))
    {
        SetPosition({ 0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / static_cast<double>(2), GetPosition().y });
    }
    if (GetPosition().x < 0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / static_cast<double>(2))
    {
        SetPosition({ Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / static_cast<double>(2),0 });
    }

    if (GetPosition().y > Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / static_cast<double>(2))
    {
        SetPosition({ GetPosition().x,0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / static_cast<double>(2) });
    }
    if (GetPosition().y < 0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / static_cast<double>(2))
    {
        SetPosition({ GetPosition().x, Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / static_cast<double>(2) });
    }

}
