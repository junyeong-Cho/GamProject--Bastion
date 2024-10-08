/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/


#pragma once

#include "Engine/GameObjectManager.h"
#include "Game/GameObjectTypes.h"

namespace GAM200
{
    class Particle : public GameObject
    {
    public:
        Particle(const std::filesystem::path& sprite_file);
        void Start(Math::vec2 position, Math::vec2 velocity, double max_life);
        void Start(Math::vec2 position, Math::vec2 velocity, double max_life, double dmg);
        void Update(double dt) override;
        void Draw(Math::TransformationMatrix camera_matrix) override;

        bool Alive()
        {
            return  life > 0;
        }

        GameObjectTypes Type() { return GameObjectTypes::Particle; }

    protected:
        double num;
        double life;
    };


    template<typename T>
    class ParticleManager : public Component
    {
    public:
        ParticleManager();
        ~ParticleManager();
        void Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread, double dmg = 0.0);

    private:
        std::vector<T*> particles;
        int index;
    };

    template<typename T>
    ParticleManager<T>::ParticleManager()
    {

        int count = T::MaxCount;

        for (int i = 0; i < count; i++)
        {
            T* particle = new T();
            particles.push_back(particle);

            //Added to the current game state's GameObjectManager
            Engine::GetGameStateManager().GetGSComponent<GameObjectManager>()->Add(particle);
        }

        index = 0;
    }



    template<typename T>
    ParticleManager<T>::~ParticleManager()
    {
        particles.clear();
    }

    template<typename T>
    void ParticleManager<T>::Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread, double dmg)
    {
        for (int i = 0; i < count; i++)
        {

            if (index >= particles.size())
            {
                index = 0;
            }

            if (particles[index]->Alive())
            {
                //Logging method may be different based on your framework or logger setup.
                Engine::GetLogger().LogEvent("Particle overwritten");
            }

            double angle_variation = 0.0;

            if (spread != 0)
            {
                angle_variation = ((rand() % static_cast<int>(spread * 1024)) / 1024.0) - spread / 2;
            }

            Math::vec2 random_magnitude = direction * (((rand() % 1024) / 2048.0) + 0.5);
            Math::vec2 particle_velocity = Math::RotationMatrix(angle_variation) * random_magnitude + emitter_velocity;

            particles[index]->Start(emitter_position, particle_velocity, T::MaxLife, dmg);

            index++;

            if (index >= particles.size())
            {
                index = 0;
            }
        }
    }


}


