#pragma once

#include "Unit.h"

class TransformUnit : public Unit
{
public:
    TransformUnit(double transform_cool, double transform_time, double T_attack_time ,double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.0);

    virtual void Update(double dt) override;
    virtual void Draw(Math::TransformationMatrix camera_matrix);

    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual GameObjectTypes Type() override { return GameObjectTypes::TransformUnit; }
    virtual std::string TypeName() override { return "TransformUnit"; }

    enum class anm
    {
        none,
        attack
    };

protected:
    double T_attack_time = 0.0;

    double transform_count = 0.0;
    double transform_time = 0.0;
    double transform_cool = 0.0;

    bool transformed = false;

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

    State_None      state_none;
    State_Attack    state_attacking;
};

class Transform_2 : public TransformUnit
{
public:
    Transform_2(Math::vec2 position = Map::middle_point) : TransformUnit(10.0, 5.0, 0.8, 1.2, 4, position)
    {
        if (transformed == false)
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform_default/deform_default.spt", (this)));
        }
        else
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform/deform.spt", (this)));
        }
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Transform_2, GameObjectTypes::Transform_4 });
        merge_list.insert({ GameObjectTypes::Spear_2, GameObjectTypes::AtkspdBuff_4 });
        merge_list.insert({ GameObjectTypes::Sniper_2, GameObjectTypes::DmgBuff_4 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Transform_2; }
    virtual std::string TypeName() override { return "Transform_2"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Transform_4 : public TransformUnit
{
public:
    Transform_4(Math::vec2 position = Map::middle_point) : TransformUnit(10.0, 5.0, 1.2, 1.5, 10, position)
    {
        if (transformed == false)
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform_default/deform_default.spt", (this)));
        }
        else
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform/deform.spt", (this)));
        }
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Transform_4, GameObjectTypes::Transform_8 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Transform_4; }
    virtual std::string TypeName() override { return "Transform_4"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Transform_8 : public TransformUnit
{
public:
    Transform_8(Math::vec2 position = Map::middle_point) : TransformUnit(10.0, 5.0, 1.2, 1.5, 30, position)
    {
        if (transformed == false)
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform_default/deform_default.spt", (this)));
        }
        else
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform/deform.spt", (this)));
        }
        current_state = &state_none;
        current_state->Enter(this);

        merge_list.insert({ GameObjectTypes::Transform_8, GameObjectTypes::Transform_16 });
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Transform_8; }
    virtual std::string TypeName() override { return "Transform_8"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};

class Transform_16 : public TransformUnit
{
public:
    Transform_16(Math::vec2 position = Map::middle_point) : TransformUnit(10.0, 5.0, 1.0, 1.4, 70, position)
    {
        if (transformed == false)
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform_default/deform_default.spt", (this)));
        }
        else
        {
            AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/deform/deform.spt", (this)));
        }
        current_state = &state_none;
        current_state->Enter(this);

    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Transform_16; }
    virtual std::string TypeName() override { return "Transform_16"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
};