/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"

#include "Fonts.h"



constexpr double meteor_timer = 4.5;

class Ship;

class Mode2 : public CS230::GameState 
{

public:
    Mode2();
    void Load()             override;
    void Update(double dt)  override;
    void Unload()           override;
    void Draw()             override;



    std::string GetName() override { return "Mode2"; }

private:
       
    Ship* ship;

    //Meteor* meteor;


    CS230::Texture game_over;
    CS230::Texture rToRestart;

    CS230::Texture scoreTexture;


    int counter = 0;
    Math::vec2 ship_position;


};