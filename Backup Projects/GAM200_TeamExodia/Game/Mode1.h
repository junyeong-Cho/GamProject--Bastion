/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"
#include "../Engine/TextureManager.h"

#include "../Engine/Particle.h"
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"
#include "../Engine/Camera.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/Texture.h"
#include "../Engine/Font.h"


#include "Background.h"
#include "Gravity.h"
#include "Score.h"


class Cat;

class Mode1 : public CS230::GameState
{
public:
    Mode1();
    void Load()            override;
    void Update(double dt) override;
    void Unload()          override;
    void Draw()            override;
    
    

    //Because there is no definition of the meter so the gravity is big
    static constexpr double gravity = 800;
    static constexpr double floor = 80;


    std::string GetName() override { return "Mode1"; }


private:
    
    int catScore = 0;
    int maxTimer = 60;

    CS230::Texture score;
    CS230::Texture timer_texture;
    Cat* cat_ptr;

    int counter = 0;
};