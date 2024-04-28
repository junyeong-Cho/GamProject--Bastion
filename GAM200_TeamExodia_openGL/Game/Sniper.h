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
};  

class Sniper_2 : public SniperUnit
{
public:
    Sniper_2(Math::vec2 position = Map::middle_point) : SniperUnit(5.0, 50, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_2; }
    virtual std::string TypeName() override { return "Sniper_2"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
    void ResolveCollision(GameObject* other_object) override;

private:
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

class Sniper_4 : public SniperUnit
{
public:
    Sniper_4(Math::vec2 position = Map::middle_point) : SniperUnit(4.0, 50, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_4; }
    virtual std::string TypeName() override { return "Sniper_4"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
    void ResolveCollision(GameObject* other_object) override;

private:
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

class Sniper_8 : public SniperUnit
{
public:
    Sniper_8(Math::vec2 position = Map::middle_point) : SniperUnit(4.0, 100, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_8; }
    virtual std::string TypeName() override { return "Sniper_8"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
    void ResolveCollision(GameObject* other_object) override;

private:
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

class Sniper_16 : public SniperUnit
{
public:
    Sniper_16(Math::vec2 position = Map::middle_point) : SniperUnit(4.0, 300, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_16; }
    virtual std::string TypeName() override { return "Sniper_16"; }

    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;
    void ResolveCollision(GameObject* other_object) override;

private:
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