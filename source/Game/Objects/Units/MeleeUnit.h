#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Transform.h"

#include "Game/Fonts.h"

class MeleeUnit : public Unit
{
public:
    MeleeUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 0.75);

    virtual void Update(double dt) override;

    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::MeleeUnit; }
    virtual std::string TypeName() override { return "MeleeUnit"; }
    
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


    State_None      state_none;
    State_Attack state_attacking;
    State_Stun      state_stun;

    double stun_time = 1.0;
    double stun_count = 0;
};




class Sword_1 : public MeleeUnit
{
public:
    Sword_1(Math::vec2 position = Map::middle_point) : MeleeUnit(2.0, 2, position) 
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);
        
        merge_list.insert({ GameObjectTypes::Sword_1, GameObjectTypes::Sword_2 });
        merge_list.insert({ GameObjectTypes::Bow_1, GameObjectTypes::Transform_2 });
        merge_list.insert({ GameObjectTypes::Bomb_1, GameObjectTypes::Spear_2 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_1; }
    std::string TypeName() override { return "Sword_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Sword_2 : public MeleeUnit
{
public:
    Sword_2(Math::vec2 position = Map::middle_point) : MeleeUnit(2.0, 6, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sword_2, GameObjectTypes::Sword_4 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_2; }
    std::string TypeName() override { return "Sword_2"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_4 : public MeleeUnit
{
public:
    Sword_4(Math::vec2 position = Map::middle_point) : MeleeUnit(1.8, 18, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sword_4, GameObjectTypes::Sword_8 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_4; }
    std::string TypeName() override { return "Sword_4"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_8 : public MeleeUnit
{
public:
    Sword_8(Math::vec2 position = Map::middle_point) : MeleeUnit(1.8, 56, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Sword_8, GameObjectTypes::Sword_16 });
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_8; }
    std::string TypeName() override { return "Sword_8"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_16 : public MeleeUnit
{
public:
    Sword_16(Math::vec2 position = Map::middle_point) : MeleeUnit(1.5, 150, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_16; }
    std::string TypeName() override { return "Sword_16"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};