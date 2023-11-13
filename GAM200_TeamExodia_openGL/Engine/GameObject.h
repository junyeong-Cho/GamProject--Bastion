/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/


#pragma once


#include "../Engine/Sprite.h"

namespace Math { class TransformationMatrix; }

enum class GameObjectTypes;

namespace GAM200
{
    class Component;

    class GameObject
    {
    public:

        friend class Sprite;


        GameObject(Math::vec2 position);
        GameObject(Math::vec2 position, double rotation, Math::vec2 scale);
        virtual ~GameObject() {}

        virtual GameObjectTypes Type() = 0;
        virtual std::string TypeName() = 0;

        bool IsCollidingWith(GameObject* other_object);
        bool IsCollidingWith(Math::vec2 point);


        void Destroy();
        bool Destroyed();

        virtual bool CanCollideWith(GameObjectTypes other_object_type);

        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix);
        virtual void ResolveCollision(GameObject* other_object) {}

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec2& GetPosition() const;
        const Math::vec2& GetVelocity() const;
        const Math::vec2& GetScale() const;
        double GetRotation() const;

        double GetSquareDistance(GameObject*);

        class State
        {
        public:
            virtual void Enter(GameObject* object) = 0;
            virtual void Update(GameObject* object, double dt) = 0;
            virtual void CheckExit(GameObject* object) = 0;
            virtual std::string GetName() = 0;
        };

        State* current_state;

        void change_state(State* new_state);

        void SetPosition(Math::vec2 new_position);

        template<typename T>
        T* GetGOComponent()
        {
            return componentmanagers.GetComponent<T>();
        }


    protected:
        bool destroy;

        void UpdatePosition(Math::vec2 delta);

        void SetVelocity(Math::vec2 new_position);
        void UpdateVelocity(Math::vec2 delta);

        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);

        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);

        void AddGOComponent(Component* component)
        {
            componentmanagers.AddComponent(component);
        }

        template<typename T>
        void RemoveGOComponent()
        {
            componentmanagers.RemoveComponent<T>();
        }
        void ClearGOComponents()
        {
            componentmanagers.Clear();
        }
        void UpdateGOComponents(double dt)
        {
            componentmanagers.UpdateAll(dt);
        }


    private:
        Math::TransformationMatrix object_matrix;

        double rotation;
        Math::vec2 scale;
        Math::vec2 position;
        Math::vec2 velocity;

        bool matrix_outdated;

        class State_None : public State
        {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;
        
        ComponentManager componentmanagers;
    };
}


