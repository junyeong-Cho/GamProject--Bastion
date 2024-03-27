#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Sniper.h"



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



class Bomb_1 : public MagicUnit
{
public:
    Bomb_1(Math::vec2 position = Map::middle_point) : MagicUnit(1.5, 4, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_1; }
    std::string TypeName() override { return "Bomb_1"; }

    void Draw(Math::TransformationMatrix camera_matrix);

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    GAM200::Texture* bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
    GAM200::Texture* bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");


};


class Bomb_2 : public MagicUnit
{
public:
    Bomb_2(Math::vec2 position = Map::middle_point) : MagicUnit(1.0, 4, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_2; }
    std::string TypeName() override { return "Bomb_2"; }

    void Draw(Math::TransformationMatrix camera_matrix);

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    GAM200::Texture* bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
    GAM200::Texture* bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");


};