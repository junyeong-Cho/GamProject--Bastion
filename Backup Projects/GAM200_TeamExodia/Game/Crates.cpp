/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#include "Crates.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"

Crates::Crates(Math::vec2 position, int size) : CS230::GameObject(position) {
    
    switch (size) 
    {
    case 1:
        AddGOComponent(new CS230::Sprite("Assets/Crates1.spt", (this)));
        break;
    case 2:
        AddGOComponent(new CS230::Sprite("Assets/Crates2.spt", (this)));
        break;
    case 3:
        AddGOComponent(new CS230::Sprite("Assets/Crates3.spt", (this)));
        break;
    case 5:
        AddGOComponent(new CS230::Sprite("Assets/Crates5.spt", (this)));
        break;
    }
}
