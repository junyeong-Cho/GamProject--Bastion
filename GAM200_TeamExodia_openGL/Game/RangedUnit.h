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

protected:
    double attack_count = 0.0;
    double attack_time = 0.0;
    int damage = 0;

};



class Bow_1 : public RangedUnit
{
public:
    Bow_1(Math::vec2 position = Map::middle_point) : RangedUnit(0.8, 2, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_1; }
    std::string TypeName() override { return "Bow_1"; }

    void Draw(Math::TransformationMatrix camera_matrix);

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    GAM200::Texture* shooter_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/shooter_idle.png");
    GAM200::Texture* shooter_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/shooter_attack.png");

};


class Bow_2 : public RangedUnit
{
public:
    Bow_2(Math::vec2 position = Map::middle_point) : RangedUnit(0.7, 3, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bow_2; }
    std::string TypeName() override { return "Bow_2"; }

    void Draw(Math::TransformationMatrix camera_matrix);

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    GAM200::Texture* shooter_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/shooter_idle.png");
    GAM200::Texture* shooter_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/shooter_attack.png");

};