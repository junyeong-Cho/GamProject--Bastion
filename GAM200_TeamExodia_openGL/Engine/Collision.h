/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.h
Project:    GAM200 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

//Collision backup code
/*
#pragma once

#include "Collision.h"
#include "Component.h"
#include "Rect.h"


namespace Math
{
    class TransformationMatrix;
}

namespace GAM200
{

    class GameObject;

    class Collision : public GAM200::Component
    {
    public:
        enum class CollisionShape
        {
            Rect,
            Circle
        };

        virtual CollisionShape Shape() = 0;


        virtual bool IsCollidingWith(GameObject* other_object) = 0;

        virtual bool IsCollidingWith(Math::vec2  point) = 0;


        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;


    };

    class RectCollision : public Collision
    {
    public:
        RectCollision(Math::irect boundary, GameObject* object);

        CollisionShape Shape() override
        {
            return CollisionShape::Rect;
        }

        bool IsCollidingWith(Math::vec2 point) override;
        bool IsCollidingWith(GameObject* other_object) override;

        void Draw(Math::TransformationMatrix display_matrix) override;

        Math::rect WorldBoundary();
    private:
        GameObject* object;
        Math::irect boundary;
    };


    //class CircleCollision : public Collision
    //{
    //public:
    //    CircleCollision(double radius, GAM200::GameObject* object);

    //    CollisionShape Shape() override
    //    {
    //        return CollisionShape::Circle;
    //    }

    //    bool IsCollidingWith(Math::vec2 point) override;
    //    bool IsCollidingWith(GameObject* other_object) override;

    //    void Draw(Math::TransformationMatrix display_matrix);

    //    //double GetRadius();

    //private:
    //    GAM200::GameObject* object;

    //    //double radius;
    //};

}

*/



#pragma once




#include "Collision.h"
#include "Component.h"
#include "Rect.h"




namespace Math
{
    class TransformationMatrix;
}

namespace GAM200
{

    class GameObject;

    class Collision : public GAM200::Component
    {
    public:
        enum class CollisionShape
        {
            Rect,
            Circle
        };

        virtual CollisionShape Shape() = 0;


        virtual bool IsCollidingWith(GameObject* other_object) = 0;

        virtual bool IsCollidingWith(Math::vec2  point) = 0;


        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;



    };

    class RectCollision : public Collision
    {
    public:
        RectCollision(Math::irect boundary, GameObject* object);
        CollisionShape Shape() override
        {
            return CollisionShape::Rect;
        }

        bool IsCollidingWith(Math::vec2 point) override;
        bool IsCollidingWith(GameObject* other_object) override;
        void Draw(Math::TransformationMatrix display_matrix) override;
        Math::rect WorldBoundary();
    private:
        GameObject* object;
        Math::irect boundary;
    };


    class CircleCollision : public Collision
    {
    public:
        CircleCollision(double radius, GAM200::GameObject* object);
        CollisionShape Shape() override
        {
            return CollisionShape::Circle;
        }

        bool IsCollidingWith(Math::vec2 point) override;
        bool IsCollidingWith(GameObject* other_object) override;
        void Draw(Math::TransformationMatrix display_matrix);
        double GetRadius();

    private:
        GAM200::GameObject* object;

        double radius;
    };

}





