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
        static constexpr double MaxLife  = 0.3;

        void Draw(Math::TransformationMatrix camera_matrix) override
        {
            if (Alive())
            {
                ShaderDrawing::draw_text(std::to_string(num), GetPosition().x, GetPosition().y, 25, 1.0, 1.0, 1.0);
            }
        }
    };
}

