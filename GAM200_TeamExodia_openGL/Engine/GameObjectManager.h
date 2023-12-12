/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#pragma once
#include <vector>
#include <list>

#include "GameObject.h"

#include "../Engine/Matrix.h"
#include "../Engine/Component.h"

namespace Math { class TransformationMatrix; }
class Monster;
class Player;

namespace GAM200
{
    class GameObjectManager : public GAM200::Component
    {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);

        void CollisionTest();
        Monster* GetClosestMonster(GAM200::GameObject*);
        std::vector<Monster*> GetMonstersInRange(GAM200::GameObject*, double);
        Player* GetPlayer();

    private:
        std::list<GameObject*> objects;
    };
}

