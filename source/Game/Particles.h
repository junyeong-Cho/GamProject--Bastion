/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particles.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "Engine/GameObjectManager.h"
#include "Engine/Particle.h"

#include "Game/GameObjectTypes.h"



namespace Particles
{
    class Smoke : public GAM200::Particle
    {
    public:
        Smoke() : Particle("Assets/Smoke.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5;
    };


    class Hit : public GAM200::Particle
    {
    public:
        Hit() : Particle("Assets/Hit.spt") { };
        std::string TypeName() override { return "Hit Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr int MaxLife = 1;
    };


    class MeteorBit : public GAM200::Particle
    {
    public:
        MeteorBit() : Particle("Assets/MeteorBit.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr int MaxLife = 1;
    };


    class FontParticle : public GAM200::Particle
    {
    public:
        FontParticle() : Particle("Assets/MeteorBit.spt") { };

        std::string TypeName() override { return "Font Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife  = 0.7;

        void Draw(Math::TransformationMatrix camera_matrix) override
        {
            if (Alive())
            {
                if (num <= 20)
                {
                    r = g = b = 1.0f;
                    scale     = 20;
                }
                else if (num <= 50)
                {
                    r = 1.0f;
                    g     = 0.5f;
                    b     = 0.0f;
                    scale = 25;
                }
                else
                {
                    r = 1.0f;
                    g = b = 0.0f;
                    scale = 30;
                }
                a *= 0.99f;

                
                std::ostringstream stream;
                stream << std::fixed << std::setprecision(1) << num;
                std::string result = stream.str();
                ShaderDrawing::draw_text(result, static_cast<float>(GetPosition().x), static_cast<float>(GetPosition().y), scale, r, g, b, a);
            }
        }

    private:
        float r, g, b = 1.0f;
        float a = 1.0f;
        float scale = 10.0;

    };
}

