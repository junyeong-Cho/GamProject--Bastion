#pragma once

#include "../Engine/GameObject.h"
#include "Bullet.h"

class Tower : public GAM200::GameObject {
public:
    Tower(Math::vec2 position);

    GameObjectTypes Type() override { return GameObjectTypes::Tower; }
    std::string TypeName() override { return "Tower"; }

    void Update(double dt) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

protected:
    struct Color {
        float r;
        float g;
        float b;
    };
    Color color = { 0 };
    Color charging_color;
    Color attack_color;

    enum class Animations
    {
        Charging,
        Attacking,
    };

    int size = 80;

    const double attack_delay = 1.0;
    double attack_count = 0;

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

};

class Basic_Tower : public Tower {
public:
    Basic_Tower(Math::vec2 position);

    GameObjectTypes Type() override { return GameObjectTypes::Basic_Tower; }
    std::string TypeName() override { return "Basic_Tower"; }

private:

};