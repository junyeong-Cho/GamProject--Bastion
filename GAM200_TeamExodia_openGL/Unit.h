#pragma once

#include "../Engine/GameObject.h"

class Unit : public GAM200::GameObject
{
public:
	Unit(Math::vec2 position) : GameObject(position) { }

	virtual void Update(double dt) override = 0;

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
    class State_Skill: public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Skill"; }
    };

    State_None      state_none;
    State_Attack    state_attacking;
    State_Skill     state_skill;

protected:
    int cost;

	double attack_count;
	double attack_speed;

	double physical_damage;
    double magical_damage;

	double skill_count;
	double skill_cooltime;

    double attack_range;

	Math::vec2 position;

    bool clicked = false;
};

