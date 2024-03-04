/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Bullet.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "../Engine/GameObjectManager.h"
#include "../Engine/Matrix.h"
#include "../Game/GameObjectTypes.h"

class Bullet : public GAM200::GameObject {
public:
    Bullet(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Bullet; }
    std::string TypeName() override { return "Bullet"; }
    virtual void Update(double dt) override;
    virtual bool CanCollideWith(GameObjectTypes other_object_type) override;
    virtual void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 900;

    static int GetDamage() { return damage; }

    Math::vec2 GetDirection() const { return direction; }


protected:

    Math::ivec2 size{ 10, 10 };

    Math::vec2 direction;

    static constexpr int damage = 1;

    struct Color {
        float r;
        float g;
        float b;
    } color;
};


class Basic_Bullet : public Bullet
{
public:
    Basic_Bullet(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Basic_Bullet; }
    std::string TypeName() override { return "Basic_Bullet"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 900;

    static int GetDamage() { return damage; }

private:

    static constexpr int damage = 1;
};


class Wide_Range_Bullet : public Bullet
{
public:
    Wide_Range_Bullet(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Wide_Range_Bullet; }
    std::string TypeName() override { return "Wide_Range_Bullet"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 900;

    static int GetDamage() { return damage; }

private:

    static constexpr int damage = 2;
};


class Pushing_Bullet : public Bullet
{
public:
    Pushing_Bullet(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Pushing_Bullet; }
    std::string TypeName() override { return "Pushing_Bullet"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 900;

    static int GetDamage() { return damage; }

private:

    static constexpr int damage = 1;

    static constexpr double push_distance = 80.0;
    double distance_count = 0.0;
};


class Monster_Heal : public Bullet
{
public:
    Monster_Heal(Math::vec2 pos, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Monster_Heal; }
    std::string TypeName() override { return "MonsterHeal"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    void Draw(Math::TransformationMatrix camera_matrix) override;

    static constexpr double DefaultVelocity = 900;

    static int GetDamage() { return damage; }

private:

    static constexpr int damage = 1;
};

