#pragma once
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/


#pragma once


#include "..\Engine\GameObject.h" 
#include "../Engine/Constants.h"
#include "..\Engine\Input.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Matrix.h"
#include "../Engine/Particle.h"

#include "Timer.h"
#include "Gravity.h"
#include "GameObjectTypes.h"



class Cat : public CS230::GameObject
{
public:
    Cat(Math::vec2 start_position, GameObject* starting_floor_ptr);

    GameObjectTypes Type() override { return GameObjectTypes::Cat; }
    std::string TypeName() override { return "Cat"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix);


    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;

    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }


private:
    enum class Animations
    {
        Idle,
        Running,
        Jumping,
        Falling,
        Skidding
    };

    GameObject* standing_on;



    Timer* hurt_timer;
    

    static constexpr double LargeFallHeight = 250.0;

    static constexpr double hurt_time = 2.0;

    const double speed = 140;

    static constexpr double bounce_velocity = 700;
    static constexpr double hurt_velocity = 350;
    static constexpr double jump_velocity = 650;
    static constexpr double pop_velocity = 400;
    static constexpr double max_velocity = 300;

    static constexpr double x_acceleration = 140;
    static constexpr double hurt_acceleration = 300;

    static constexpr double x_drag = 50;

    double fall_start_position_y;


    void update_x_velocity(double dt);






    //Finite State Machines
    class State_Jumping : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Idle : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Falling : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    class State_Running : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    class State_Skidding : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };



    State_Jumping state_jumping;

    State_Idle state_idle;

    State_Falling state_falling;

    State_Running state_running;

    State_Skidding state_skidding;

};
