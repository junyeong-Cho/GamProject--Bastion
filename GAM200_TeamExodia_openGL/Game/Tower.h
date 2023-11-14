#pragma once

#include "../Engine/GameObject.h"
#include "Bullet.h"
#include "../Engine/Texture.h"
class Tower : public GAM200::GameObject {
public:
    Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Tower; }
    std::string TypeName() override { return "Tower"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static int GetCost() { return cost; }

    int GetHP() const { return hp; }
    void SetHP(int value) { hp = value; }

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

    int size_x = 0;
    int size_y = 0;

    int direction;
    Math::vec2 bullet_direction;

    const double attack_delay = 1.0;
    double attack_count = 0;
    ///
    bool four_way[4] = { false,false,false,false };//tower_way_select
    ///
    int max_hp = 10;
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
    static const int cost = 0;
};

class Basic_Tower : public Tower {
public:
    Basic_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Tower; }
    std::string TypeName() override { return "Basic_Tower"; }

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
    static const int cost = 100;
};

class Double_Tower : public Tower
{
public:
    Double_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Double_Tower; }
    std::string TypeName() override { return "Double_Tower"; }

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
    static const int cost = 200;

};

class Triple_Tower : public Tower
{
public:
    Triple_Tower(Math::vec2 position, int direction);

    GameObjectTypes Type() override { return GameObjectTypes::Triple_Tower; }
    std::string TypeName() override { return "Triple_Tower"; }

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
    static const int cost = 300;

};