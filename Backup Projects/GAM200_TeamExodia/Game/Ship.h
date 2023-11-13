#pragma once
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "GameObjectTypes.h"

#include "..\Engine\GameObjectManager.h"
#include "..\Engine\Collision.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

#include "../Game/Laser.h"


class Ship : public CS230::GameObject
{
public:
    Ship(Math::vec2 start_position);

    GameObjectTypes Type() override { return GameObjectTypes::Ship; }
    std::string TypeName() override { return "Ship"; }


    void Update(double dt) override;

    bool CanCollideWith(GameObjectTypes object_type) override;

    void ResolveCollision(GameObject* other_object) override;

    bool Exploded();


    void Draw(Math::TransformationMatrix camera_matrix) override;


    enum class Flame_Animations
    {
        None,
        Flame
    };

    enum class Animations
    {
        None,
        Explosion
    };


    bool is_thrusting = false;
    bool is_idle = false;

private:

    bool exploded;
    
    bool flame = false;

    CS230::Sprite flame_left;
    CS230::Sprite flame_right;

    Math::vec2   start_position;



    static constexpr double rotation_speed = 2.0;

    const double ship_speed = 140;
    
    static constexpr double scale = 0.75;

    static constexpr double speed = 700;
    static constexpr double drag = 1;
};
