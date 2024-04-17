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

    GAM200::Texture* bomb_idle = nullptr;
    GAM200::Texture* bomb_attack = nullptr;

    virtual void Draw(Math::TransformationMatrix camera_matrix);
};



class Bomb_1 : public MagicUnit
{
public:
    Bomb_1(Math::vec2 position = Map::middle_point) : MagicUnit(1.5, 4, position) 
    {
        bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
        bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_1; }
    std::string TypeName() override { return "Bomb_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:

};


class Bomb_2 : public MagicUnit
{
public:
    Bomb_2(Math::vec2 position = Map::middle_point) : MagicUnit(1.0, 4, position)
    {
        bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
        bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_2; }
    std::string TypeName() override { return "Bomb_2"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:

};


class Bomb_4 : public MagicUnit
{
public:
    Bomb_4(Math::vec2 position = Map::middle_point) : MagicUnit(1.5, 10, position)
    {
        bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
        bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_4; }
    std::string TypeName() override { return "Bomb_4"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:

};


class Bomb_8 : public MagicUnit
{
public:
    Bomb_8(Math::vec2 position = Map::middle_point) : MagicUnit(1.0, 20, position)
    {
        bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
        bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_8; }
    std::string TypeName() override { return "Bomb_8"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:

};


class Bomb_16 : public MagicUnit
{
public:
    Bomb_16(Math::vec2 position = Map::middle_point) : MagicUnit(0.8, 30, position)
    {
        bomb_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_idle.png");
        bomb_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/bomb_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Bomb_16; }
    std::string TypeName() override { return "Bomb_16"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:

};