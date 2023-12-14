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
#include "../Engine/Audio.h"

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
    void Recover() { if (recover_enabled) life_count = max_life; }
    static void EnableRecover() { recover_enabled = true; }
    static int GetAdditionalDmg() { return additional_attack_dmg; }

    static void UpgradeAttackSpeed() { attack_cool *= 0.5; }
    static void UpgradeAttackDmg() { ++additional_attack_dmg; }
    static void EnableShotGun() { shot_gun_mode = true; }
    static void EnableGodMode() { god_mode = true; }


    int GetDashCount() const { return dash_life; }
    void SetDashCount(int dash) { dash_life = dash; }

    double GetDashSpeedMultiplier() const { return dash_speed_multiplier; }
    double GetDashCooltime() const { return dash_cool; }

    bool GetDashActive() const { return dash_active; }
    void SetDashActive(bool active) { dash_active = active; }

    enum class arm_anm
    {
        None,

        arm_fire

    };
    enum class boost_anm
    {
        None,

        front,
        right,
        back,
        left,

        front_right,
        front_left,

        back_right,
        back_left

    };

    enum class dash_anm
    {
        dash_none,

        front_move_dash,
        back_move_dash,
        left_move_dash,
        right_move_dash,

        front_right_dash,
        front_left_dash,

        back_right_dash,
        back_left_dash

    };
    GAM200::Sprite arm;
    GAM200::Sprite boost;
    GAM200::Sprite dash;
    GAM200::Sprite muzzle_effect;

    bool bullet_is_fired = false;
    bool is_thrusting = false;
    bool is_fired = false;
private:



    GAM200::Texture p = GAM200::Texture("assets/images/p.png", GAM200::Texture::TextureType::RECTANGLE);

    enum class Animations
    {
        Idle,
        Front_Moving,
        Rihgt_Moving,
        Back_Moving,
        Left_Moving,
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


    int dash_right = 0;
    int dash_left = 0;
    int dash_front = 1;
    int dash_back = 1;
    int dash_accel = 1;
    bool dash_on[4] = { false, false, false, false };//wasd
    bool four_way_dash_on = false;

    static bool recover_enabled;
    static constexpr double invincibilityTime = 1.0;
    double invincibility_count = 0;

    static double attack_cool;
    double attack_count = 0;

    static int additional_attack_dmg;

    int max_life = 20;
    int life_count = 0;

    static bool shot_gun_mode;
    static bool god_mode;


    static constexpr double dash_cool = 1.0;
    bool dash_active = true;
    double dash_speed_multiplier = 4.0;
    double dash_count = 0;
    double dash_life = 5;
    static constexpr double dash_original_life = 5;
    double dash_latency = 1;

    //Finite State Machines
    class State_Idle : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "idle"; }
    };




    class Front_Moving : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "front"; }
    };


    class Right_Moving : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "right"; }
    };


    class Back_Moving : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "back"; }
    };


    class Left_Moving : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "left"; }
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

    Front_Moving Front_Moving;
    Right_Moving Right_Moving;
    Back_Moving Back_Moving;
    Left_Moving Left_Moving;

    State_Dashing state_dashing;
    State_Skidding state_skidding;

};
