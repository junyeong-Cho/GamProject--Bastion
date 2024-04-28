#pragma once

#include "Unit.h"


class SpearUnit : public Unit
{
public:
    SpearUnit(double attack_time, int damage, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 2.5);

    virtual void Update(double dt) override;


    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;


    virtual GameObjectTypes Type() override { return GameObjectTypes::SpearUnit; }
    virtual std::string TypeName() override { return "SpearUnit"; }

    enum class anm
    {
        none,
        attack
    };
  
   
protected:
    virtual void Draw(Math::TransformationMatrix camera_matrix);

};

class Spear_2 : public SpearUnit
{
public:
    Spear_2(Math::vec2 position = Map::middle_point) : SpearUnit(1.2, 2, position) 
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;


    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear_2; }
    virtual std::string TypeName() override { return "Spear_2"; };

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

class Spear_4 : public SpearUnit
{
public:
    Spear_4(Math::vec2 position = Map::middle_point) : SpearUnit(1.2, 5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;


    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear_4; }
    virtual std::string TypeName() override { return "Spear_4"; };

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

class Spear_8 : public SpearUnit
{
public:
    Spear_8(Math::vec2 position = Map::middle_point) : SpearUnit(1.0, 15, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;


    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear_8; }
    virtual std::string TypeName() override { return "Spear_8"; };

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

class Spear_16 : public SpearUnit
{
public:
    Spear_16(Math::vec2 position = Map::middle_point) : SpearUnit(1.0, 50, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/gunner_default.spt", (this)));
        current_state = &state_none;
        current_state->Enter(this);

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;


    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear_16; }
    virtual std::string TypeName() override { return "Spear_16"; };

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