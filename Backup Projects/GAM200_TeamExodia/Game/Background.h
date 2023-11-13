/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#pragma once
#include <doodle/drawing.hpp>

#include "../Engine/Component.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Engine.h"


class Background : public CS230::Component
{
public:
    void Add(const std::filesystem::path& texturePath, double speed);
    void Unload();
    void Draw(const CS230::Camera& camera);
    Math::ivec2 GetSize();

private:
    struct ParallaxLayer 
    {
        CS230::Texture* texture;
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;
};