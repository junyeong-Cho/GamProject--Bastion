/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#include "ShowCollision.h"

#include "Engine.h"

GAM200::ShowCollision::ShowCollision() : enabled(true) {}


void GAM200::ShowCollision::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tidle)) {
        enabled = !(enabled);
    }
}

bool GAM200::ShowCollision::Enabled()
{
    return enabled;
}
