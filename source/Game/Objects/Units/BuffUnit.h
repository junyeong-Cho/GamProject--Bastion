#pragma once

#include "Unit.h"


class DmgBuffUnit : public Unit
{
public:
    DmgBuffUnit(double buff_amount, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 1.5);

    virtual void Update(double dt) override;

    virtual bool CanCollideWith(GameObjectTypes type) override;
    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual double GetBuffAmount()
    {
        return buff_amount;
    }

    virtual GameObjectTypes Type() override
    {
        return GameObjectTypes::BuffUnit;
    }

    virtual std::string TypeName() override
    {
        return "BuffUnit";
    }

protected:
    virtual void Draw(Math::TransformationMatrix camera_matrix);
    bool         restart = false;

    double buff_amount = 0;
};


class DmgBuff_4 : public DmgBuffUnit
{
public:
    DmgBuff_4(Math::vec2 position = Map::middle_point) : DmgBuffUnit(1.5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_damage/support_damage_default.spt", (this)));

        merge_list.insert({ GameObjectTypes::DmgBuff_4, GameObjectTypes::DmgBuff_8 });
    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::DmgBuff_4;
    }

    std::string TypeName() override
    {
        return "DmgBuff_4";
    };

    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};

class DmgBuff_8 : public DmgBuffUnit
{
public:
    DmgBuff_8(Math::vec2 position = Map::middle_point) : DmgBuffUnit(2.5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_damage/support_damage_default.spt", (this)));

        merge_list.insert({ GameObjectTypes::DmgBuff_8, GameObjectTypes::DmgBuff_16 });
    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::DmgBuff_8;
    }

    std::string TypeName() override
    {
        return "DmgBuff_8";
    };

    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};

class DmgBuff_16 : public DmgBuffUnit
{
public:
    DmgBuff_16(Math::vec2 position = Map::middle_point) : DmgBuffUnit(6.5, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_damage/support_damage_default.spt", (this)));

    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::DmgBuff_16;
    }

    std::string TypeName() override
    {
        return "DmgBuff_16";
    };

    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};

class AtkspdBuffUnit : public Unit
{
public:
    AtkspdBuffUnit(double buff_amount, Math::vec2 position = Map::middle_point, double range = Map::basic_size * 1.5);

    virtual void Update(double dt) override;

    virtual bool CanCollideWith(GameObjectTypes type) override;
    virtual void ResolveCollision(GameObject* other_object) override;
    virtual bool CanMergeWith(GameObjectTypes type) override;
    virtual void ResolveMerge(GameObject* other_object) override;

    virtual double GetBuffAmount()
    {
        return buff_amount;
    }

    virtual GameObjectTypes Type() override
    {
        return GameObjectTypes::BuffUnit;
    }

protected:
    virtual void Draw(Math::TransformationMatrix camera_matrix);
    bool         restart = false;

    double buff_amount = 0;
};

class AtkspdBuff_4 : public AtkspdBuffUnit
{
public:
    AtkspdBuff_4(Math::vec2 position = Map::middle_point) : AtkspdBuffUnit(0.9, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_speed/support_speed_default.spt", (this)));

    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::AtkspdBuff_4;
    }

    std::string TypeName() override
    {
        return "AtkspdBuff_4";
    };
    
    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};

class AtkspdBuff_8 : public AtkspdBuffUnit
{
public:
    AtkspdBuff_8(Math::vec2 position = Map::middle_point) : AtkspdBuffUnit(0.8, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_speed/support_speed_default.spt", (this)));

    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::AtkspdBuff_8;
    }

    std::string TypeName() override
    {
        return "AtkspdBuff_8";
    };

    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};

class AtkspdBuff_16 : public AtkspdBuffUnit
{
public:
    AtkspdBuff_16(Math::vec2 position = Map::middle_point) : AtkspdBuffUnit(0.6, position)
    {
        AddGOComponent(new GAM200::Sprite("assets/tower_s2/animation/support_speed/support_speed_default.spt", (this)));

    }

    GameObjectTypes Type() override
    {
        return GameObjectTypes::AtkspdBuff_16;
    }

    std::string TypeName() override
    {
        return "AtkspdBuff_16";
    };

    bool CanMergeWith(GameObjectTypes type) override;
    void ResolveMerge(GameObject* other_object) override;
};