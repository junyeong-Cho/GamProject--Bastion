#pragma once

#include "../Engine/GameObject.h"

#include "GameObjectTypes.h"
#include "../Component/Map.h"
#include "../Engine/Component.h"
#include "../Engine/Matrix.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Texture.h"


class Unit : public GAM200::GameObject
{
public:
    Unit(double range, Math::vec2 position);
    ~Unit();

    virtual void Update(double dt);
    virtual void Draw(Math::TransformationMatrix camera_matrix);

    GameObjectTypes Type() override { return GameObjectTypes::Unit; }
    std::string TypeName() override { return "Unit"; }

    virtual bool CanCollideWith(GameObjectTypes type) override
    {
        return type == GameObjectTypes::Monster ? true : false;
    }
    virtual void ResolveCollision(GameObject* other_object) override = 0;

    virtual bool CanMergeWith(GameObjectTypes type) override = 0;
    virtual void ResolveMerge(GameObject* other_object) override = 0;


    void HandleMouseInput();
    bool IsInMap(Math::vec2 position) const;
    bool IsMouseOverUnit() const;

    double GetRadius() const { return radius; }

    double range;
    static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0; 
    bool is_moving = false;

protected:
    double attack_animation_count = 0.0;
    double attack_animation_time = 0.1;

    bool not_clicked = true;

   
    bool drop = false;
    bool is_colliding = false;
    bool possible_to_merge = false;


    Math::vec2 position_gap;
};
