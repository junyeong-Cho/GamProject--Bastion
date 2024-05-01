#pragma once

#include "Engine/GameObject.h"



#include "Component/Map.h"

#include "Engine/Component.h"
#include "Engine/Matrix.h"
#include "Engine/DrawShape.h"
#include "Engine/Texture.h"

#include "Game/Fonts.h"
#include "Game/GameObjectTypes.h"



#include <queue>

class Unit : public GAM200::GameObject
{
public:
    Unit(double attack_time, int damage, double range, Math::vec2 position);
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

    virtual void ShowInfo();

    void HandleMouseInput();
    bool IsInMap(Math::vec2 position) const;
    Math::vec2 LimitInMap(Math::vec2 position);
    bool IsMouseOverUnit() const;

    double GetRadius() const { return radius; }
    double GetRange() const { return range; }

    static constexpr double dps_time_cap = 10.0;
    void UpdateDPS();
    double GetDPS();
    void InsertDPS(int damage);

    double range;
    static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0;
    bool is_moving = false;

    bool AttackReady() const { return attack_count >= attack_time; }

protected:
    double attack_count = 0.0;
    double attack_time = 0.0;
    int damage = 0;

    double attack_animation_count = 0.0;
    double attack_animation_time = 0.1;

    bool not_clicked = true;


    bool drop = false;
    bool is_colliding = false;
    bool possible_to_merge = false;

    std::queue<std::pair<double, int>>damageHolder;

    Math::vec2 position_gap;



    std::unique_ptr<GAM200::Texture> name;
    std::unique_ptr<GAM200::Texture> dmg;
    std::unique_ptr<GAM200::Texture> attackSpd;
    std::unique_ptr<GAM200::Texture> dps;
};
