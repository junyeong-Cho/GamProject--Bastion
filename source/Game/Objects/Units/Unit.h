#pragma once

#include "Engine/GameObject.h"
#include "Engine/IfWantShader.h"

#include "Game/GameObjectTypes.h"
#include "Component/Map.h"
#include "Engine/Component.h"
#include "Engine/Matrix.h"
#include "Engine/DrawShape.h"
#include "Engine/Texture.h"

#include "Game/Fonts.h"

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
        return (type == GameObjectTypes::Monster) ? true : false;
    }
    virtual void ResolveCollision(GameObject* other_object) override = 0;

    virtual bool CanMergeWith(GameObjectTypes type) override = 0;
    virtual void ResolveMerge(GameObject* other_object) override = 0;

    void DrawMergeList();

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
    void InsertDPS(double damage);

    void BuffDmg(double dmg);
    void BuffAtkspd(double atkspd);
    void ResetBuff();

    double GetDamage() const
    {
        return damage * damage_buff;
    }

    double GetAtkSpd() const
    {
        return attack_time * atkspd_buff;
    }

    void SetDamage(double new_damage)
    {
        damage = new_damage;
    }
   
    void SetAtkSpd(double newAttackTime)
    {
        attack_time *= newAttackTime;
    }

    double range;
    static inline double radius = Map::basic_size * 3.0 / 4.0 / 2.0; 
    bool is_moving = false;

    bool AttackReady() const { return attack_count >= GetAtkSpd(); }

    bool stunned = false;

protected:
    double attack_count = 0.0;
    double attack_time = 0.0;
    double damage = 0.0;

    double damage_buff = 1.0;
    double atkspd_buff = 1.0;

    double attack_animation_count = 0.0;
    double attack_animation_time = 0.1;

    bool not_clicked = true;

   
    bool drop = false;
    bool is_colliding = false;
    bool possible_to_merge = false;

    std::queue<std::pair<double, double>>damageHolder;
 
    Math::vec2 position_gap;

    std::unordered_map<GameObjectTypes, GameObjectTypes> merge_list;
    std::unordered_map<GameObjectTypes, ShaderDrawing::Image> imageCache;
    ShaderDrawing::Image&                                     getImage(GameObjectTypes type);

#if IfWantShader

#else
    std::unique_ptr<GAM200::Texture> dmg;
    std::unique_ptr<GAM200::Texture> attackSpd;
    std::unique_ptr<GAM200::Texture> dps;
#endif
};