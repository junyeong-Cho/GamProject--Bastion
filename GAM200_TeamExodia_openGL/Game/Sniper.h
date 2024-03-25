#pragma once

#include "Unit.h"

class SniperUnit : public Unit
{
public:
    SniperUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 4.0);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::SniperUnit; }
    virtual std::string TypeName() override { return "SniperUnit"; }

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

class Sniper : public SniperUnit
{
public:
    Sniper(Math::vec2 position = Map::middle_point) : SniperUnit(5.0, 7, position) { }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper; }
    virtual std::string TypeName() override { return "Sniper"; }
};