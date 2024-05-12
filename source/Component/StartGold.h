/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Life.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "Engine/GameStateManager.h"

class StartGold : public GAM200::Component
{
public:
    StartGold() : startGold(110)
    { }

    int GetStartGold() const { return startGold; }
    void AddStartGold(int value) { startGold += value; }

private:
    int startGold;
};