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

    double stun_time  = 5.0;
    double stun_count = 0;
};



class Bow_1 : public RangedUnit
{
public:
    Bow_1(Math::vec2 position = Map::middle_point) : RangedUnit(3.2, 2, position) 
    { 
       AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sword_1, GameObjectTypes::Transform_2 });
        merge_list.insert({ GameObjectTypes::Bow_1, GameObjectTypes::Bow_2 });
        merge_list.insert({ GameObjectTypes::Bomb_1, GameObjectTypes::Sniper_2 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_1; }
    std::string TypeName() override { return "Bow_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bow_2 : public RangedUnit
{
public:
    Bow_2(Math::vec2 position = Map::middle_point) : RangedUnit(3.0, 5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_2.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bow_2, GameObjectTypes::Bow_4 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_2; }
    std::string TypeName() override { return "Bow_2"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bow_4 : public RangedUnit
{
public:
    Bow_4(Math::vec2 position = Map::middle_point) : RangedUnit(2.8, 20, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_4.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bow_4, GameObjectTypes::Bow_8 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_4; }
    std::string TypeName() override { return "Bow_4"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bow_8 : public RangedUnit
{
public:
    Bow_8(Math::vec2 position = Map::middle_point) : RangedUnit(2.8, 66, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_8.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bow_8, GameObjectTypes::Bow_16 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_8; }
    std::string TypeName() override { return "Bow_8"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bow_16 : public RangedUnit
{
public:
    Bow_16(Math::vec2 position = Map::middle_point) : RangedUnit(2.5, 200, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_16.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

    }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_16; }
    std::string TypeName() override { return "Bow_16"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Rambo_4 : public RangedUnit
{
public:
    Rambo_4(Math::vec2 position = Map::middle_point) : RangedUnit(2.8, 15, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Rambo_4, GameObjectTypes::Rambo_8 });
    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::Rambo_4;
    }

    std::string TypeName() override
    {
        return "Rambo_4";
    }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Rambo_8 : public RangedUnit
{
public:
    Rambo_8(Math::vec2 position = Map::middle_point) : RangedUnit(2.8, 40, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Rambo_8, GameObjectTypes::Rambo_16 });
    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::Rambo_8;
    }

    std::string TypeName() override
    {
        return "Rambo_8";
    }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Rambo_16 : public RangedUnit
{
public:
    Rambo_16(Math::vec2 position = Map::middle_point) : RangedUnit(2.0, 100, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::Rambo_16;
    }

    std::string TypeName() override
    {
        return "Rambo_16";
    }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};