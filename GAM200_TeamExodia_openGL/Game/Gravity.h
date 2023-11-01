/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Gravity.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#pragma once

#include "../Engine/ComponentManager.h"

class Gravity : public GAM200::Component
{
public:
    Gravity(double value) : gravity(value) {}
    double GetValue() { return gravity; }
private:
    double gravity;
};
