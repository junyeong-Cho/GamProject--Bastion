/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 2, 2023
Updated:    November 2, 2023
*/

#pragma once


#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

class Splash : public GAM200::GameState
{
public:
    Splash();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;



    std::string GetName() override { return "Splash"; }
public:

    double counter = 0;
    GAM200::Texture* texture;
};
