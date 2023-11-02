/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"

#include "Fonts.h"

#include "Score.h"


constexpr double meteor_timer = 4.5;

class Ship;

class Mode2 : public GAM200::GameState
{

public:
    Mode2();
    void Load()             override;
    void Update(double dt)  override;
    void Unload()           override;
    void Draw()             override;

    void         ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;


    std::string GetName() override { return "Mode2"; }

private:

    Ship* ship;

    //Meteor* meteor;


    GAM200::Texture* game_over;
    GAM200::Texture* rToRestart;

    GAM200::Texture* scoreTexture;


    int counter = 0;
    Math::vec2 ship_position;


};