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

class Sniper_2 : public SniperUnit
{
public:
    Sniper_2(Math::vec2 position = Map::middle_point) : SniperUnit(5.0, 7, position) { }

    virtual GameObjectTypes Type() override { return GameObjectTypes::Sniper_2; }
    virtual std::string TypeName() override { return "Sniper_2"; }


    void Draw(Math::TransformationMatrix camera_matrix)
    {
        Unit::Draw(camera_matrix);

        Math::vec2 position = GetPosition();

        // Unit draw   
        if (current_state->GetName() == "None")
        {
            sniper_attack->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
        }
        else
        {
            sniper_idle->Draw(static_cast<int>(position.x) - 85 / 2, static_cast<int>(position.y), 170 / 2, 185 / 2);
        }
    }

private:
    GAM200::Texture* sniper_idle = Engine::Instance().GetTextureManager().Load("assets/tower_s2/sniper_idle.png");
    GAM200::Texture* sniper_attack = Engine::Instance().GetTextureManager().Load("assets/tower_s2/sniper_attack.png");
    

};