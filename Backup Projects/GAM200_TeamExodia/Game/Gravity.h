/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Gravity.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/

#pragma once

#include "../Engine/ComponentManager.h"

class Gravity : public CS230::Component 
{
public:
    Gravity(double value) : gravity(value) {}
    double GetValue() { return gravity; }
private:
    double gravity;
};
