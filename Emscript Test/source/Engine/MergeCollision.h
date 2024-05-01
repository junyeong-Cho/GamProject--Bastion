/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MergeCollision.h
Project:    GAM200_TeamExodia_openGL
Author:     HyeonJoon Nam
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "Component.h"
#include "Engine/Rect.h"

namespace Math
{
    class TransformationMatrix;
}

namespace GAM200
{

    class GameObject;

    class MergeCollision : public GAM200::Component
    {
    public:
        virtual bool IsMergingWith(GameObject* other_object) = 0;
        virtual bool IsMergingWith(Math::vec2  point) = 0;
    };

    class MergeCircleCollision : public MergeCollision
    {
    public:
        MergeCircleCollision(double radius, GAM200::GameObject* object);

        bool IsMergingWith(Math::vec2 point) override;
        bool IsMergingWith(GameObject* other_object) override;
        void Draw(Math::TransformationMatrix display_matrix);
        double GetRadius();

    private:
        GAM200::GameObject* object;

        double radius;
    };

}