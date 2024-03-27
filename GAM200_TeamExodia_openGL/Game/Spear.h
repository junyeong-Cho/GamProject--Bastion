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

class Spear_2 : public SpearUnit
{
public:
    Spear_2(Math::vec2 position = Map::middle_point) : SpearUnit(1.2, 2, position) { }


    virtual GameObjectTypes Type() override { return GameObjectTypes::Spear_2; }
    virtual std::string TypeName() override { return "Spear_2"; }

    void Draw(Math::TransformationMatrix camera_matrix)
    {
        Unit::Draw(camera_matrix);

        Math::vec2 position = GetPosition();

        // Unit draw   
        if (current_state->GetName() == "None")
        {
            spear_attack->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 260 / 2, 155 / 2);
        }
        else
        {
            spear_attack->Draw(static_cast<int>(position.x) - 130 / 2, static_cast<int>(position.y), 260 / 2, 155 / 2);
        }
    }

private:
    GAM200::Texture* spear_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/spear_idle.png");
    GAM200::Texture* spear_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/spear_attack.png");
};