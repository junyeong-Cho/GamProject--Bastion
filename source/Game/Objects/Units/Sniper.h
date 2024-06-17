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
    
    enum class anm
    {
        none,
        attack
    };

protected:
    virtual void Draw(Math::TransformationMatrix camera_matrix);
    bool restart = false;

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
    class State_Stun : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;

        std::string GetName() override
        {
            return "Stun";
        }
    };

    State_None   state_none;
    State_Attack state_attacking;
    State_Stun   state_stun;

    double stun_time  = 1.0;
    double stun_count = 0;
};  

class Sniper_2 : public SniperUnit
{
public:
    Sniper_2(Math::vec2 position = Map::middle_point) : SniperUnit(5.0, 10, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sniper/sniper_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::, GameObjectTypes::Sniper_4 });
        merge_list.insert({ GameObjectTypes::Spear_2, GameObjectTypes::Rambo_4 });
        merge_list.insert({ GameObjectTypes::Transform_2, GameObjectTypes::DmgBuff_4 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_2; }
    virtual std::string TypeName() override { return "Sniper_2"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Sniper_4 : public SniperUnit
{
public:
    Sniper_4(Math::vec2 position = Map::middle_point) : SniperUnit(4.5, 30, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sniper/sniper4.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sniper_4, GameObjectTypes::Sniper_8 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_4; }
    virtual std::string TypeName() override { return "Sniper_4"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Sniper_8 : public SniperUnit
{
public:
    Sniper_8(Math::vec2 position = Map::middle_point) : SniperUnit(4.3, 90, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sniper/sniper8.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sniper_8, GameObjectTypes::Sniper_16 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_8; }
    virtual std::string TypeName() override { return "Sniper_8"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Sniper_16 : public SniperUnit
{
public:
    Sniper_16(Math::vec2 position = Map::middle_point) : SniperUnit(4.0, 200, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sniper/sniper16.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_16; }
    virtual std::string TypeName() override { return "Sniper_16"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};