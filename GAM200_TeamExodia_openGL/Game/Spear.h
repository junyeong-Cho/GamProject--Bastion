#pragma once

#include "Unit.h"


class SpearUnit : public Unit
{
public:
    SpearUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.5);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::SpearUnit; }
    virtual std::string TypeName() override { return "SpearUnit"; }

protected:
    class State_None : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "None"; }
    };
    class State_Attack : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attack"; }
    };

    State_None      state_none;
    State_Attack    state_attacking;

protected:
    double attack_count = 0.0;
    double attack_time = 0.0;
    int damage = 0;

};

class Spear : public SpearUnit
{
public:
    Spear(Math::vec2 position = Map::middle_point) : SpearUnit(1.2, 2, position) { }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear; }
    virtual std::string TypeName() override { return "Spear"; }
};