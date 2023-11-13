/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robots.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/


#pragma once

#include "GameObjectTypes.h"
#include "Score.h"
#include "Cat.h"

#include "../Engine/GameObject.h"
#include "../Game/States.h"


class Robot : public CS230::GameObject 
{
public:
    Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary);


    void ResolveCollision(GameObject* other_object) override;

    GameObjectTypes Type() override { return GameObjectTypes::Robot; }
    std::string TypeName() override { return "Robot"; }

private:
    
    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed   = 105.0;
    
    enum class Animations
    {
        None,
        Walking,
        Angry,
        Dead,
    };

    enum class WalkingDirection {Left, Right};

    WalkingDirection m_walking_direction = WalkingDirection::Right;

    Cat*   m_cat;
    double m_left_boundary;
    double m_right_boundary;




    //Finite State Machine
    class State_Dead : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dead"; }
    };

    class State_Walking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Walking"; }
    };

    class State_Angry : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };

    State_Dead    state_dead;
    State_Walking state_walking;
    State_Angry   state_angry;


};
