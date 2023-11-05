/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/


#include<vector>

#include "../Game/Floor.h"

#include "../Engine/Engine.h" 
#include "../Engine/Window.h"
#include "../Engine/Matrix.h"
#include "../Engine/Collision.h"
#include "../Engine/ShowCollision.h"

#include "Particles.h"
#include "Asteroid.h"
#include "Portal.h"
#include "Crates.h"
#include "States.h"
#include "Robots.h"
#include "Timer.h"
#include "Cat.h"


#include "Mode1.h"
#include "Fonts.h"
#include <imgui.h>


Mode1::Mode1()
{
 //   score_texture = nullptr;
}



void Mode1::Load()
{

    AddGSComponent(new GAM200::GameObjectManager());

    AddGSComponent(new GAM200::ShowCollision());

    AddGSComponent(new Gravity(Mode1::gravity));

    AddGSComponent(new Timer(maxTimer));

    AddGSComponent(new Background());

    AddGSComponent(new Score());

    AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));

    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 930, static_cast<int>(floor) } });
    GetGSComponent<GAM200::GameObjectManager>()->Add(starting_floor_ptr);
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Floor(Math::irect{ { 1014, 0 }, { 2700, static_cast<int>(floor) } }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Floor(Math::irect{ { 2884, 0 }, { 4126, static_cast<int>(floor) } }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Floor(Math::irect{ { 4208, 0 }, { 5760, static_cast<int>(floor) } }));

    //  GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 400, 100 }, { 700, 50 } }));

    GetGSComponent<GAM200::GameObjectManager>()->Add(new Portal(static_cast<int>(States::MainMenu), Math::irect{ { 5700, 50 }, { 5800, 1000 } }));


    cat_ptr = new Cat({ 300, floor }, starting_floor_ptr);
    GetGSComponent<GAM200::GameObjectManager>()->Add(cat_ptr);

    AddGSComponent(new GAM200::ParticleManager<Particles::Smoke>());

    GetGSComponent<Background>()->Add("assets/Planets.png", 0.25);
    GetGSComponent<Background>()->Add("assets/Ships.png", 0.5);
    GetGSComponent<Background>()->Add("assets/Foreground.png", 1);


    GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });
    GetGSComponent<GAM200::Camera>()->SetLimit({ {0, 0},{GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize()} });


    GetGSComponent<GAM200::GameObjectManager>()->Add(new Asteroid({ 600, floor }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Asteroid({ 1800, floor }));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Asteroid({ 2400, floor }));

    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 900, floor }, 2));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 1400, floor }, 1));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 2000, floor }, 5));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 4000, floor }, 3));


    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 5400, floor }, 1));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 5500, floor }, 3));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Crates({ 5600, floor }, 5));

    //Old robot of logic
    /*
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 1200, Mode1::floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 2200, Mode1::floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 3400, Mode1::floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 4200, Mode1::floor }));
    */

    //Test floor code for collision check
    /*
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 400, 100 }, { 700, 50 } }));
    */

    GetGSComponent<GAM200::GameObjectManager>()->Add(new Robot({ 1025, floor }, cat_ptr, 1025, 1350));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Robot({ 2050, floor }, cat_ptr, 2050, 2325));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Robot({ 3400, floor }, cat_ptr, 3400, 3800));
    GetGSComponent<GAM200::GameObjectManager>()->Add(new Robot({ 4225, floor }, cat_ptr, 4225, 4800));



#ifdef _DEBUG
    AddGSComponent(new GAM200::ShowCollision());
#endif

}


void Mode1::Update(double dt)
{
    GetGSComponent<GAM200::Camera>()->Update(cat_ptr->GetPosition());
    GetGSComponent<Timer>()->Update(dt);
    GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<GAM200::ShowCollision>()->Update(dt);
    GetGSComponent<Score>()->Update(dt);


    int remaining_time = GetGSComponent<Timer>()->GetRemainingTime();
    int catScore = GetGSComponent<Score>()->Value();

    /*
    if (timer_texture != nullptr) 
    {
        delete timer_texture;
        timer_texture = nullptr;
    }
    */

    timer_texture.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(remaining_time), 0xFFFFFFFF));
    score.reset(Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(catScore), 0xFFFFFFFF));

   // timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(remaining_time), 0xFFFFFFFF);

   // timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(remaining_time), 0xFFFFFFFF);
   //score = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(catScore), 0xFFFFFFFF);


    if (remaining_time == 0)
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }

    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }


    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::R))
    {
        Engine::GetGameStateManager().ReloadGameState();
    }
}


void Mode1::Unload()
{
    cat_ptr = nullptr;
    timer_texture = nullptr;


//    delete timer_texture;
    GetGSComponent<Background>()->Unload();
    GetGSComponent<GAM200::GameObjectManager>()->Unload();
    ClearGSComponent();
}


void Mode1::Draw()
{
    Engine::GetWindow().Clear(0.0, 0.0, 0.0, 1.0);

    Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();


    GetGSComponent<Background>()->Draw(*GetGSComponent<GAM200::Camera>());


    timer_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture->GetSize().x, Engine::GetWindow().GetSize().y}));
    score->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture->GetSize().x, Engine::GetWindow().GetSize().y + timer_texture->GetSize().y}));

    GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
}

void Mode1::ImguiDraw()
{
    ImGui::Begin("Program Info");
    {
        ImGui::Text("Player position: %.3f, %.3f", cat_ptr->GetPosition().x, cat_ptr->GetPosition().y);
        ImGui::Text("Camera position: %.3f, %.3f", GetGSComponent<GAM200::Camera>()->GetPosition().x, GetGSComponent<GAM200::Camera>()->GetPosition().y);

        float velocity_f = static_cast<float>(cat_ptr->GetMaxVelocity());

        if (ImGui::SliderFloat("Max Velocity", &velocity_f, 100.0f, 600.0f, "%.0f"))
        {
            cat_ptr->SetMaxVelocity(velocity_f);
        }   


    }
    ImGui::End();
}

void Mode1::HandleEvent(SDL_Event& event)
{

}
