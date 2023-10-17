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
#include "../Game/GameObjectTypes.h"

#include "../Game/AStar.h"

class Monster : public GAM200::GameObject {
public:
	Monster(Math::vec2 position, Player* player);

	void ResolveCollision(GameObject* other_object) override;

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

protected:
    std::vector<Math::ivec2> path;

    double resisting_count = 0;
    const double resisting_time = 0.5;

    int tile_index;
    Math::ivec2 current_tile_position;
    Math::ivec2 next_tile_position;

    int size = 40;
    int walking_speed = 175;

    int score = 1;
    int gold = 10;

    struct FillColor {
        float r = 0;
        float g = 0;
        float b = 0;
    } fill_color;

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

private:

};

class Basic_Monster : public Monster {
public:
    Basic_Monster(Math::vec2 position, Player* player);

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Monster; }
    std::string TypeName() override { return "Basic_Monster"; }

};

class Fast_Monster : public Monster {
public:
    Fast_Monster(Math::vec2 position, Player* player);

    GameObjectTypes Type() override { return GameObjectTypes::Fast_Monster; }
    std::string TypeName() override { return "Fast_Monster"; }

};