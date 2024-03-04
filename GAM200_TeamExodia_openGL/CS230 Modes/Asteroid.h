/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/
#pragma once

#include "..\Engine\GameObject.h" 
#include "GameObjectTypes.h"




class Asteroid : public GAM200::GameObject
{
public:
    Asteroid(Math::vec2 start_position);


    GameObjectTypes Type() override { return GameObjectTypes::Asteroid; }
    std::string TypeName() override { return "Asteroid"; }


    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


private:
    enum class Animations
    {
        None,
        AsteroidLand,
    };


    //how fast the jump speed
    static constexpr double bounce_velocity = 500;


    class State_Bouncing : public State
    {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Bouncing"; }
    };

    class State_Landing : public State
    {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Landing"; }
    };

    State_Bouncing state_bouncing;

    State_Landing state_landing;
};

