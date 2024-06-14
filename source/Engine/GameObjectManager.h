/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#pragma once
#include <vector>
#include <list>

#include "GameObject.h"

#include "Engine/Matrix.h"
#include "Engine/Component.h"

namespace Math { class TransformationMatrix; }

class Unit;
class Monster;

namespace GAM200
{
    class GameObjectManager : public GAM200::Component
    {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);
        void DrawParticle(Math::TransformationMatrix camera_matrix);
        void CollisionTest();
        void MergeTest();

        Unit* GetClosestUnit(Unit* unit);
        Unit* GetClosestUnit(Math::vec2 position);

        Unit* GetCurrentUnit() const { return current_unit; }
        void ResetCurrentUnit() { current_unit = nullptr; }

        Unit* GetInfoTarget() const { return info_target; }
        Unit* SetInfoTarget(Unit* unit) { info_target = unit; }
        void ResetInfoTarget() { info_target = nullptr; }

        void StunUnits(Math::vec2 position, double range);

        bool IsMonserNear(Unit* unit);
        Monster* GetClosestMonster(Unit* unit);
        Monster* GetClosestMonster(Math::vec2 position);
        void DeleteAllMonster();
        double WideDamage(Math::vec2 position, double radius, double damage);
        void ApplyDebuff(double debuffFactor);

    private:
        std::list<GameObject*> objects;

        Unit* current_unit = nullptr;
        Unit* info_target  = nullptr;
    };
}

