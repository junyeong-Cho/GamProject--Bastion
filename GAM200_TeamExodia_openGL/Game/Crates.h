/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once

#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"

class Crates : public GAM200::GameObject
{
public:
    Crates(Math::vec2 position, int size);

    GameObjectTypes Type() override { return GameObjectTypes::Crates; }
    std::string TypeName() override { return "Crates"; }
};
