/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Player.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		10, 2023
*/

#pragma once

#include "../Engine/GameObject.h"

#include "../Game/Player.h"
#include "../Game/States.h"

#include "Mode1.h"


class Monster : public GAM200::GameObject {
public:
	Monster(Math::vec2 position, Player* player);

	void ResolveCollision(GameObject* other_object) override;

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

private:
    static constexpr double size = 40.0;
    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed = 105.0;

    enum class Animations
    {
        None,
        Walking,
        Dead,
    };

    enum class WalkingDirection { Left, Right, UP, DOWN };

    WalkingDirection m_walking_direction = WalkingDirection::Right;

    Player* m_player;
    Math::irect boundary;
    /*double m_left_boundary;
    double m_right_boundary;*/


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


    State_Dead    state_dead;
    State_Walking state_walking;

};