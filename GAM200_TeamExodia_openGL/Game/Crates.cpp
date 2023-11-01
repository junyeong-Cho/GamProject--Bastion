/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Crates.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"

Crates::Crates(Math::vec2 position, int size) : GAM200::GameObject(position) {

    switch (size)
    {
    case 1:
        AddGOComponent(new GAM200::Sprite("Assets/Crates1.spt", (this)));
        break;
    case 2:
        AddGOComponent(new GAM200::Sprite("Assets/Crates2.spt", (this)));
        break;
    case 3:
        AddGOComponent(new GAM200::Sprite("Assets/Crates3.spt", (this)));
        break;
    case 5:
        AddGOComponent(new GAM200::Sprite("Assets/Crates5.spt", (this)));
        break;
    }
}
