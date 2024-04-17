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

    /*virtual void ShowInfo() override
    {
        std::unique_ptr<GAM200::Texture> trash;
        trash.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("!!!", 0xFFFFFFFF));
        trash->Draw(Math::TranslationMatrix(Math::ivec2{ 50, 50 }));    

        std::unique_ptr<GAM200::Texture> name;
        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
        name->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 420 }));

        std::unique_ptr<GAM200::Texture> dmg;
        dmg.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Damage: " + std::to_string(damage), 0xFFFFFFFF));
        dmg->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 350 }));

        std::unique_ptr<GAM200::Texture> attackSpd;
        attackSpd.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Attack Speed: " + std::to_string(attack_time), 0xFFFFFFFF));
        attackSpd->Draw(Math::TranslationMatrix(Math::ivec2{ 900, 280 }));
    }*/
    
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

    GAM200::Texture* melee_idle = nullptr;
    GAM200::Texture* melee_attack = nullptr;

    virtual void Draw(Math::TransformationMatrix camera_matrix);

};




class Sword_1 : public MeleeUnit
{
public:
    Sword_1(Math::vec2 position = Map::middle_point) : MeleeUnit(1.0, 5, position) 
    {
        melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
        melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_1; }
    std::string TypeName() override { return "Sword_1"; }

    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    /*GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");*/
};


class Sword_2 : public MeleeUnit
{
public:
    Sword_2(Math::vec2 position = Map::middle_point) : MeleeUnit(1.0, 10, position)
    {
        melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
        melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_2; }
    std::string TypeName() override { return "Sword_2"; }


    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    /*GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");*/
};

class Sword_4 : public MeleeUnit
{
public:
    Sword_4(Math::vec2 position = Map::middle_point) : MeleeUnit(1.0, 25, position)
    {
        melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
        melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_4; }
    std::string TypeName() override { return "Sword_4"; }


    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    /*GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");*/
};

class Sword_8 : public MeleeUnit
{
public:
    Sword_8(Math::vec2 position = Map::middle_point) : MeleeUnit(0.8, 60, position)
    {
        melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
        melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_8; }
    std::string TypeName() override { return "Sword_8"; }


    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    /*GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");*/
};

class Sword_16 : public MeleeUnit
{
public:
    Sword_16(Math::vec2 position = Map::middle_point) : MeleeUnit(0.7, 200, position)
    {
        melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
        melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");

        name.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Name: " + TypeName(), 0xFFFFFFFF));
    }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_16; }
    std::string TypeName() override { return "Sword_16"; }


    bool CanMergeWith(GameObjectTypes type);
    void ResolveMerge(GameObject* other_object);

private:
    /*GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");*/
};