#pragma once

#include "Monster.h"
#include "Engine/Collision.h"

#include "Engine/GameObject.h"
#include "Game/GameObjectTypes.h"

#include "Component/Map.h"

class Boss : public Monster
{
public:
    Boss() : Monster({ 500, 10, 0.5 })
    {
        AddGOComponent(new GAM200::Sprite("assets/enemy_s2/Boss.spt", (this)));

        current_state = &state_none;
        current_state->Enter(this);
    }

    
	virtual void Draw(Math::TransformationMatrix camera_matrix) override;

    enum NextPattern
    {
        Summon,
        Stun
    } next_pattern = Summon;

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

    inline static double pattern_time_count = 0.0;

    inline static double summon_pattern_cool_time = 10.0;
    inline static double summon_time              = 5.0;
    double summon_time_count = 0;
    inline static double summon_num               = 5;
    double summon_num_count  = 0;

    inline static double stun_pattern_delay     = 3.0;
    inline static double stun_pattern_cool_time = 10.0;
    double stun_count   = 0;
    inline static double stun_range             = Map::basic_size * 3.0;
};