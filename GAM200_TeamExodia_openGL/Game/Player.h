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
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Texture.h"
#include "../Game/GameObjectTypes.h"

class Player : public GAM200::GameObject {
public:
    Player(Math::vec2 start_position, int size_x, int size_y);

	GameObjectTypes Type() override { return GameObjectTypes::Player; }
	std::string TypeName() override { return "Player"; }

	void Update(double dt) override;

	void Draw(Math::TransformationMatrix camera_matrix) override;


	bool CanCollideWith(GameObjectTypes type) override;

	void ResolveCollision(GameObject* other_object) override;

	const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    int GetHP() const { return life_count; }
    void SetHP(int life) { life_count = life; }

private:



    GAM200::Texture p = GAM200::Texture("assets/images/p.png", GAM200::Texture::TextureType::RECTANGLE);

    enum class Animations
    {
        Idle,
        Moving,
        Dashing,
        Skidding,
    };

    const double speed = 140;
    int size;
    int size_x;
    int size_y;

    static constexpr double max_velocity = 300;
    static constexpr double dash_velocity = 500;

    static constexpr double acceleration = 300;

    static constexpr double drag = 200;

    bool not_clicked = false;

    void update_velocity(double dt);

    static constexpr double invincibilityTime = 1.0;
    double invincibility_count = 0;

    static constexpr double attack_cool = 0.5;
    double attack_count = 0;

    int max_life = 50;
    int life_count = 0;


    //Finite State Machines
    class State_Idle : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Moving : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Dashing : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    class State_Skidding : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    
    State_Idle state_idle;

    State_Moving state_moving;

    State_Dashing state_dashing;

    State_Skidding state_skidding;

};
