#pragma once

#include "Unit.h"
#include "Transform.h"
#include "Sniper.h"



class RangedUnit : public Unit
{
public:
    RangedUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.5);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::RangedUnit; }
    virtual std::string TypeName() override { return "RangedUnit"; }


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

class Bow : public RangedUnit
{
public:
    Bow(Math::vec2 position = Map::middle_point) : RangedUnit(0.8, 2, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bow; }
    std::string TypeName() override { return "Bow"; }

    bool CanMergeWith(GameObjectTypes type)
    {
        switch (type)
        {
        case GameObjectTypes::Sword:
            return true;

        case GameObjectTypes::Bomb:
            return true;

        default:
            return false;
        }
    }
    void ResolveMerge(GameObject* other_object)
    {
        if (other_object->Type() == GameObjectTypes::Sword)
        {
            new Transform(GetPosition());
            other_object->Destroy();
            Destroy();
        }
        else if (other_object->Type() == GameObjectTypes::Bomb)
        {
            new Sniper(GetPosition());
            other_object->Destroy();
            Destroy();
        }
    }
};