/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#include "../Engine/Engine.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/GameObjectManager.h"

#include "States.h"
#include "Meteor.h"
#include "Ship.h"

#include "Mode2.h"
#include "Particles.h"

Mode2::Mode2() 
{
        
    CS230::GameObjectManager* gameobjectmanager = new CS230::GameObjectManager();

    AddGSComponent(gameobjectmanager);

    ship = nullptr;
}

void Mode2::Load() 
{

#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif

    AddGSComponent(new CS230::GameObjectManager());


    AddGSComponent(new CS230::ParticleManager<Particles::Hit>());
    AddGSComponent(new CS230::ParticleManager<Particles::MeteorBit>());

    AddGSComponent(new Score());

    ship = new Ship({ Engine::GetWindow().GetSize().x / (double)2, Engine::GetWindow().GetSize().y / (double)2 });
    GetGSComponent<CS230::GameObjectManager>()->Add(ship);

    game_over  = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Game Over"         , 0xFFFFFFFF);
    rToRestart = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Press R to Restart", 0xFFFFFFFF);
}


void Mode2::Update(double dt) 
{
    if (!(ship->Exploded()))
    {
        UpdateGSComponents(dt);
        
        static double newElapsedTime = 0.0;
        newElapsedTime += dt;

        if (newElapsedTime >= meteor_timer)
        {
            GetGSComponent<CS230::GameObjectManager>()->Add(new Meteor());
            newElapsedTime = 0.0;
        }
    }

    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    int shipScore = GetGSComponent<Score>()->Value();

    scoreTexture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(shipScore), 0xFFFFFFFF);

     Engine::GetWindow().Clear(0x000000FF);

     if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::B))
     {
        Engine::GetGameStateManager().ClearNextGameState();
     }

     if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
     {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
     }
}

void Mode2::Unload() 
{
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponent();
}

void Mode2::Draw()
{
    Engine::GetWindow().Clear(0x000000FF);

    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

    scoreTexture.Draw(Math::TranslationMatrix(Math::ivec2{ 0, Engine::GetWindow().GetSize().y - scoreTexture.GetSize().y }));
  

    if (ship->Exploded() == true)
    {
        game_over.Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 100), (Engine::GetWindow().GetSize().y - 500) }));
        rToRestart.Draw(Math::TranslationMatrix(Math::ivec2{ (Engine::GetWindow().GetSize().x / 2 - 200), (Engine::GetWindow().GetSize().y - 200) }));

        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R))
        {
            Engine::GetGameStateManager().ReloadGameState();
        }
    }
     
}