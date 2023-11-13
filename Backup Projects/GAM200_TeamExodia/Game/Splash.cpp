/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#include "../Engine/Engine.h"
#include "../Game/States.h"
#include "../Game/Splash.h"

Splash::Splash()
{

}

void Splash::Load() 
{
    counter = 0;

    texture = Engine::Instance().GetTextureManager().Load("Assets/DigiPen.png");
}

void Splash::Update(double dt) 
{
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 2.40) 
    {
        Engine::GetGameStateManager().ClearNextGameState();

        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt; 
}

void Splash::Unload() 
{

}

void Splash::Draw()
{
     Engine::GetWindow().Clear(UINT_MAX);
     
     texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));

}


