#pragma once

#include "Monster.h"
#include "Engine/Collision.h"

class Boss : public Monster
{
public:
    Boss() : Monster(info) { }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::Boss;
    }
    std::string TypeName() override
    {
        return "Boss";
    }

private:
    MonsterInfo boss_info = MonsterInfo({ 500, 10, 1.0 });

protected:
    class State_None : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "None";
        }
    };

    class State_Summon : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "State_Summon";
        }
    };

    class State_Stun : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "State_Stun";
        }
    };

    class State_Dead : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "Dead";
        }
    };

    State_None      state_none;
    State_Summon    state_summon;
    State_Stun      state_stun;
    State_Dead      state_dead;

    double summon_time       = 0;
    double summon_time_count = 0;
    double summon_num        = 0;
    double summon_num_count  = 0;

    double stun_time    = 0;
    double stun_count   = 0;
    double stun_range = Map::basic_size * 1.5;
};