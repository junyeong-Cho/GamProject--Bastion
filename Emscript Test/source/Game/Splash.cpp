/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    December 15, 2023
*/


#include "Engine/Engine.h"
#include "Game/States.h"
#include "Game/Splash.h"

Splash::Splash()
{

}

void Splash::Load()
{
    counter = 0;

    texture = Engine::Instance().GetTextureManager().Load("assets/DigiPen.png");
}

void Splash::Update(double dt)
{
    //Engine::GetLogger().LogDebug(std::to_string(counter));


    /*if (counter >= 2.40)
    {
        Engine::GetGameStateManager().ClearNextGameState();

        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt;*/
}

void Splash::Unload()
{

}

void Splash::Draw()
{
    Engine::GetWindow().Clear(1.0, 1.0, 1.0, 1.0);
    Drawing::set_coordinate_mode(Drawing::CoordinateSystem::LEFT_DOWN);
    Drawing::set_image_mode(Drawing::DrawOriginMode::LEFT_DOWN);

    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));


}

void Splash::ImguiDraw()
{

}

void Splash::HandleEvent(SDL_Event& event)
{

}


