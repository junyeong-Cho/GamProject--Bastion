/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Monster.h
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
	Monster(Math::vec2 position = Math::vec2(0, 0));

	void ResolveCollision(GameObject* other_object) override;

	GameObjectTypes Type() override { return GameObjectTypes::Monster; }
	std::string TypeName() override { return "Monster"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    Math::vec2 GetSize() { return Math::vec2(size_x, size_y); }
    static int GetDamage() { return damage; }
    static int GetRemainMonster();

    static int remaining_monsters;
    
    Math::vec2 tile_size;

protected:
    GAM200::Texture e = GAM200::Texture("assets/images/e.png", GAM200::Texture::TextureType::RECTANGLE);

    std::vector<Math::ivec2> path;

    double resisting_count = 0;
    const double resisting_time = 0.5;
    double walking_speed;

    int life = 0;

    int real_max_life = 0;
    int real_damage = 0;
    double real_speed_scale = 0.0;
    int real_score = 0;
    int real_gold = 0;

    int tile_index;
    Math::ivec2 current_tile_position;
    Math::ivec2 next_tile_position;

    int size_x;
    int size_y;

    Math::irect boundary;

    enum class Animations
    {
        None,
        Walking,
        Dead,
    };

    enum class WalkingDirection { Left, Right, UP, DOWN };
    WalkingDirection m_walking_direction = WalkingDirection::UP;

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
    friend class MonsterFactory;

    static int max_life;
    static int damage;
    static double speed_scale;
    static int score;
    static int gold;
};



class Basic_Monster : public Monster {
public:
    Basic_Monster(Math::vec2 position = Math::vec2(0, 0));

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Monster; }
    std::string TypeName() override { return "Basic_Monster"; }

    void Update(double dt) override;

    static int GetDamage() { return damage; }

private:
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


    friend class MonsterFactory;

    static int max_life;
    static int damage;
    static double speed_scale;
    static int score;
    static int gold;
};



class Fast_Monster : public Monster {
public:
    Fast_Monster(Math::vec2 position = Math::vec2(0, 0));

    GameObjectTypes Type() override { return GameObjectTypes::Fast_Monster; }
    std::string TypeName() override { return "Fast_Monster"; }

    void Update(double dt) override;

    static int GetDamage() { return damage; }

private:
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


    friend class MonsterFactory;

    static int max_life;
    static int damage;
    static double speed_scale;
    static int score;
    static int gold;
};



class Slow_Monster : public Monster {
public:
    Slow_Monster(Math::vec2 position = Math::vec2(0, 0));

    GameObjectTypes Type() override { return GameObjectTypes::Slow_Monster; }
    std::string TypeName() override { return "Slow_Monster"; }

    void Update(double dt) override;

    static int GetDamage() { return damage; }

private:
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


    friend class MonsterFactory;

    static int max_life;
    static int damage;
    static double speed_scale;
    static int score;
    static int gold;
};



class Weak_Monster : public Monster
{
public:
    Weak_Monster(Math::vec2 position = Math::vec2(0, 0));

    GameObjectTypes Type() override { return GameObjectTypes::Weak_Monster; }
    std::string TypeName() override { return "Weak_Monster"; }

    void Update(double dt) override;

    static int GetDamage() { return damage; }

private:
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


    friend class MonsterFactory;

    static int max_life;
    static int damage;
    static double speed_scale;
    static int score;
    static int gold;
};




class MonsterFactory {
public:
    static void InitBasicMonsterFromFile(const std::string& filePath = "assets/monsters/Basic_Monster.txt");
    static void  InitFastMonsterFromFile(const std::string& filePath = "assets/monsters/Fast_Monster.txt");
    static void  InitSlowMonsterFromFile(const std::string& filePath = "assets/monsters/Slow_Monster.txt");
    static void InitWeakMonstserFromFile(const std::string& filePath = "assets/monsters/Weak_Monster.txt");

private:

};