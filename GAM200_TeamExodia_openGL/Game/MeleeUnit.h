#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Transform.h"

#include "Fonts.h"

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

    State_None      state_none;
    State_Attack    state_attacking;
};




class Sword_1 : public MeleeUnit
{
public:
    Sword_1(Math::vec2 position = Map::middle_point) : MeleeUnit(4.0, 5, position) 
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_1; }
    std::string TypeName() override { return "Sword_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};


class Sword_2 : public MeleeUnit
{
public:
    Sword_2(Math::vec2 position = Map::middle_point) : MeleeUnit(4.0, 10, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_2; }
    std::string TypeName() override { return "Sword_2"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_4 : public MeleeUnit
{
public:
    Sword_4(Math::vec2 position = Map::middle_point) : MeleeUnit(4.0, 25, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_4; }
    std::string TypeName() override { return "Sword_4"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_8 : public MeleeUnit
{
public:
    Sword_8(Math::vec2 position = Map::middle_point) : MeleeUnit(3.2, 60, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_8; }
    std::string TypeName() override { return "Sword_8"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};

class Sword_16 : public MeleeUnit
{
public:
    Sword_16(Math::vec2 position = Map::middle_point) : MeleeUnit(2.8, 200, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/sword/sword_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_16; }
    std::string TypeName() override { return "Sword_16"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);
};