/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#include "ShowCollision.h"

#include "Engine.h"

CS230::ShowCollision::ShowCollision() : enabled(true) {}


void CS230::ShowCollision::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Tidle))
    {
        enabled = !(enabled);
    }
}

bool CS230::ShowCollision::Enabled()
{
    return enabled;
}
