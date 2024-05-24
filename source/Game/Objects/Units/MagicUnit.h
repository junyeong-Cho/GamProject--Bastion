#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Sniper.h"


extern bool tutorial_merge;

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

    enum class anm
    {
        none,
        attack
    };

protected:
    bool restart = false;
    virtual void Draw(Math::TransformationMatrix camera_matrix);

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
};



class Bomb_1 : public MagicUnit
{
public:
    Bomb_1(Math::vec2 position = Map::middle_point) : MagicUnit(5.0, 1, position) 
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/bomb/bomb_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sword_1, GameObjectTypes::Spear_2 });
        merge_list.insert({ GameObjectTypes::Bow_1, GameObjectTypes::Sniper_2 });
        merge_list.insert({ GameObjectTypes::Bomb_1, GameObjectTypes::Bomb_2 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_1; }
    std::string TypeName() override { return "Bomb_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bomb_2 : public MagicUnit
{
public:
    Bomb_2(Math::vec2 position = Map::middle_point) : MagicUnit(5.0, 2, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/bomb/bomb_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bomb_2, GameObjectTypes::Bomb_4 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_2; }
    std::string TypeName() override { return "Bomb_2"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bomb_4 : public MagicUnit
{
public:
    Bomb_4(Math::vec2 position = Map::middle_point) : MagicUnit(4.8, 4, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/bomb/bomb_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bomb_4, GameObjectTypes::Bomb_8 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_4; }
    std::string TypeName() override { return "Bomb_4"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bomb_8 : public MagicUnit
{
public:
    Bomb_8(Math::vec2 position = Map::middle_point) : MagicUnit(4.7, 5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/bomb/bomb_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Bomb_8, GameObjectTypes::Bomb_16 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_8; }
    std::string TypeName() override { return "Bomb_8"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Bomb_16 : public MagicUnit
{
public:
    Bomb_16(Math::vec2 position = Map::middle_point) : MagicUnit(4.5, 15, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/bomb/bomb_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_16; }
    std::string TypeName() override { return "Bomb_16"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};