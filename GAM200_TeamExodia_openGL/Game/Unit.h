#pragma once

#include "../Engine/GameObject.h"

#include "GameObjectTypes.h"
#include "../Component/Map.h"


class Unit : public GAM200::GameObject
{
public:
    Unit(double range, Math::vec2 position);

    virtual void Update(double dt);
    virtual void Draw(Math::TransformationMatrix camera_matrix);

    GameObjectTypes Type() override { return GameObjectTypes::Unit; }
    std::string TypeName() override { return "Unit"; }

    virtual bool CanCollideWith(GameObjectTypes type) override = 0;
    virtual void ResolveCollision(GameObject* other_object) override = 0;

    virtual bool CanMergeWith(GameObjectTypes type) override = 0;
    virtual void ResolveMerge(GameObject* other_object) override = 0;


    void HandleMouseInput();
    bool IsInMap(Math::vec2 position) const;
    bool IsMouseOverUnit() const;

    double GetRadius() const { return radius; }

protected:
    double range;

    bool not_clicked = true;

    bool is_moving = false;
    bool drop = false;
    bool is_colliding = false;
    bool possible_to_merge = false;

    static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0;

    Math::vec2 position_gap;
};

class TestUnit : public Unit
{
public:
    TestUnit(double range = Map::basic_size * 0.75, Math::vec2 position = Map::middle_point) : Unit(range, position) { }


    bool CanCollideWith(GameObjectTypes type) override 
    { 
        if (type == GameObjectTypes::Monster)
            return true;
        else
            return false;
    }
    void ResolveCollision(GameObject* other_object) override { }

    bool CanMergeWith(GameObjectTypes type) override { return false; }
    void ResolveMerge(GameObject* other_object) override { }
};