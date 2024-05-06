/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Gold.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "Engine/GameStateManager.h"


class Gold : public GAM200::Component
{
public:
    Gold() : goldValue(500) {}

    void Add(int value);
    void Subtract(int value);
    int Value() const;
    void SetValue(int value) { goldValue = value; }
    void Interest();
    void Upgrade();
    void Restore();

private:
    int goldValue;

    double interest_rate = 0.2;
};