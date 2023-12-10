#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"

#include <iostream>
#include <fstream>
#include <string>



// Virtual class for the towers
class Tower : public GAM200::GameObject {
public:
    Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Tower; }
    std::string TypeName() override { return "Tower"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

	virtual bool CanCollideWith(GameObjectTypes type) override;

	virtual void ResolveCollision(GameObject* other_object) override;

    static int GetCost() { return cost; }

    int GetHP() const { return hp; }
    void SetHP(int value) { hp = value; }

    bool IsOn() const;
    bool IsClicked() const;

    void Tower_Destroy();

protected:
    bool set_basic_tower = false;
    GAM200::Texture c_down = GAM200::Texture("assets/images/c_down.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_up = GAM200::Texture("assets/images/c_up.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_left = GAM200::Texture("assets/images/c_left.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture c_right = GAM200::Texture("assets/images/c_right.png", GAM200::Texture::TextureType::RECTANGLE);

    struct Color {
        float r;
        float g;
        float b;
    };
    Color color = { 0 };
    Color charging_color;
    Color attack_color;

    enum   Animations
    {
        Charging,
        Attacking,
    };

    Math::ivec2 size{ 80, 80 };

    int direction;
    Math::vec2 bullet_direction;

    double attack_count = 0;
    bool attack_ready = false;
    ///
    bool four_way[4] = { false,false,false,false };//tower_way_select
    ///
    int hp;

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;
};


// Basic tower
class Basic_Tower : public Tower {
public:
    Basic_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Tower; }
    std::string TypeName() override { return "Basic_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


    static int GetCost() { return cost; }


    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;
};


// Double tower
class Double_Tower : public Tower
{
public:
    Double_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Double_Tower; }
    std::string TypeName() override { return "Double_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


    static int GetCost() { return cost; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;
};


// Triple tower
class Triple_Tower : public Tower
{
public:
    Triple_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Triple_Tower; }
    std::string TypeName() override { return "Triple_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


    static int GetCost() { return cost; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;
};


// Push tower
class Push_Tower : public Tower
{
public:
    Push_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Push_Tower; }
    std::string TypeName() override { return "Push_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


    static int GetCost() { return cost; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;
};


// Wide Tower
class Wide_Tower : public Tower
{
public:
    Wide_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Wide_Tower; }
    std::string TypeName() override { return "Wide_Tower"; }

    bool CanCollideWith(GameObjectTypes type) override;

    void ResolveCollision(GameObject* other_object) override;


    static int GetCost() { return cost; }

    class State_Charging : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Attacking : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Charging state_charging;
    State_Attacking state_attacking;

private:
    friend class TowerFactory;
    static int cost;
    static double attack_delay;
    static int max_hp;

    static int range_x;
    static int range_y;
    static double attack_range;
};



class TowerFactory {
public:
    static void InitBasicTowerFromFile(const std::string& filePath = "assets/towers/Basic_Tower.txt");
    static void InitDoubleTowerFromFile(const std::string& filePath = "assets/towers/Double_Tower.txt");
    static void InitTripleTowerFromFile(const std::string& filePath = "assets/towers/Triple_Tower.txt");
    static void InitPushTowerFromFile(const std::string& filePath = "assets/towers/Push_Tower.txt");
    static void InitWideTowerFromFile(const std::string& filePath = "assets/towers/Wide_Tower.txt");

private:

};
