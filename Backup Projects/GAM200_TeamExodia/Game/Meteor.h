/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "GameObjectTypes.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/Collision.h"
#include "../Engine/Sprite.h"
#include "Score.h"

class Meteor : public CS230::GameObject
{
public:
   // Meteor(Math::vec2 position);

    Meteor(Meteor* parent);

    Meteor();


    GameObjectTypes Type() override { return GameObjectTypes::Meteor; }
    std::string TypeName() override { return "Meteor"; }

    void ResolveCollision(GameObject* other_object) override;


    void Update(double dt) override;


  
    //static constexpr double default_velocity = 100;

private:
    enum class Animations
    {
        None,
        Fade,
    };

    Score* score;

    double health;

    int size;


    static constexpr double default_velocity = 100;
    static constexpr double default_size = 2;
    static constexpr double default_healths[] = { 3, 5, 8 };
    static constexpr double default_scales[] = { 0.5, 0.75, 1.0 };
  
};

