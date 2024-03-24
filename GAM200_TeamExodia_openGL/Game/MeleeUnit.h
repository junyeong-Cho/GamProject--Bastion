#pragma once

#include "Unit.h"


class MeleeUnit : public Unit
{
public:
    MeleeUnit(double range = Map::basic_size * 0.75, Math::vec2 position = Map::middle_point) : Unit(range, position) { }

    virtual void Update(double dt) override;
    //virtual void Draw(Math::TransformationMatrix camera_matrix) override;

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
    class State_Skill : public State
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

private:


};
