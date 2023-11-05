/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/
#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Engine.h"


class Background : public GAM200::Component
{
public:
    void Add(const std::filesystem::path& texturePath, double speed);
    void Unload();
    void Draw(const GAM200::Camera& camera);
    Math::ivec2 GetSize();

private:
    struct ParallaxLayer
    {
        GAM200::Texture* texture;
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;
};