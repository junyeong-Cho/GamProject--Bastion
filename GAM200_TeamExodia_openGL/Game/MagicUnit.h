#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Sniper.h"



class MagicUnit : public Unit
{
public:
    MagicUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.0);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::MagicUnit; }
    virtual std::string TypeName() override { return "MagicUnit"; }


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

class Bomb : public MagicUnit
{
public:
    Bomb(Math::vec2 position = Map::middle_point) : MagicUnit(1.2, 4, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb; }
    std::string TypeName() override { return "Bomb"; }

    bool CanMergeWith(GameObjectTypes type)
    {
        switch (type)
        {
        case GameObjectTypes::Sword:
            return true;

        case GameObjectTypes::Bow:
            return true;

        default:
            return false;
        }
    }
    void ResolveMerge(GameObject* other_object)
    {
        if (other_object->Type() == GameObjectTypes::Sword)
        {
            new Spear(GetPosition());
            other_object->Destroy();
            Destroy();
        }
        else if (other_object->Type() == GameObjectTypes::Bow)
        {
            new Sniper(GetPosition());
            other_object->Destroy();
            Destroy();
        }
    }
};