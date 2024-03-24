#pragma once

#include "Unit.h"

class TransformUnit : public Unit
{
public:
    TransformUnit(double transform_cool, double transform_time, double T_attack_time ,double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.0);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::TransformUnit; }
    virtual std::string TypeName() override { return "TransformUnit"; }

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
    double T_attack_time = 0.0;
    double transform_count = 0.0;
    double transform_time = 0.0;
    double transform_cool = 0.0;
    bool transformed = false;
    int damage = 0;

};

class Transform : public TransformUnit
{
public:
    Transform(Math::vec2 position = Map::middle_point) : TransformUnit(10.0, 5.0, 0.8, 1.2, 4, position) { }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Transform; }
    virtual std::string TypeName() override { return "Transform"; }
};