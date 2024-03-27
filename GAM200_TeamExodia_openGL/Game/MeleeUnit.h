#pragma once

#include "Unit.h"
#include "Spear.h"
#include "Transform.h"

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




class Sword_1 : public MeleeUnit
{
public:
    Sword_1(Math::vec2 position = Map::middle_point) : MeleeUnit(1.0, 3, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_1; }
    std::string TypeName() override { return "Sword_1"; }

    void Draw(Math::TransformationMatrix camera_matrix)
    {
        Unit::Draw(camera_matrix);

        Math::vec2 position = GetPosition();

        // Unit draw        
        if(current_state->GetName() == "None")
        {
            melee_attack->Draw(static_cast<int>(position.x) - 85/2, static_cast<int>(position.y), 170/2, 185/2);
        }
        else
        {
            melee_idle->Draw(static_cast<int>(position.x) - 85/2, static_cast<int>(position.y), 170/2, 185/2);
        }
     }


    bool CanMergeWith(GameObjectTypes type)
    {
        switch (type)
        {
        case GameObjectTypes::Sword_1:
            return true;

        case GameObjectTypes::Bomb_1:
            return true;

        case GameObjectTypes::Bow_1:
            return true;

        default:
            return false;
        }
    }
    void ResolveMerge(GameObject* other_object)
    {
        if (other_object->Type() == GameObjectTypes::Sword_1)
        {
            new Sword_2(GetPosition());
            other_object->Destroy();
            Destroy();
        }
        else if (other_object->Type() == GameObjectTypes::Bow_1)
        {
            new Transform_2(GetPosition());
            other_object->Destroy();
            Destroy();
        }
        else if (other_object->Type() == GameObjectTypes::Bomb_1)
        {
            new Spear_2(GetPosition());
            other_object->Destroy();
            Destroy();
        }
    }
private:
    GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");
};


class Sword_2 : public MeleeUnit
{
public:
    Sword_2(Math::vec2 position = Map::middle_point) : MeleeUnit(1.0, 4, position) { }

    GameObjectTypes Type() override { return GameObjectTypes::Sword_2; }
    std::string TypeName() override { return "Sword_2"; }

    void Draw(Math::TransformationMatrix camera_matrix)
    {
        Unit::Draw(camera_matrix);

        Math::vec2 position = GetPosition();

        // Unit draw        
        if (current_state->GetName() == "None")
        {
            melee_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
        }
        else
        {
            melee_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
        }
    }


    bool CanMergeWith(GameObjectTypes type)
    {
        switch (type)
        {
        default:
            return false;
        }
    }
    void ResolveMerge(GameObject* other_object)
    {

    }
private:
    GAM200::Texture* melee_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_idle.png");
    GAM200::Texture* melee_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/melee_attack.png");
};