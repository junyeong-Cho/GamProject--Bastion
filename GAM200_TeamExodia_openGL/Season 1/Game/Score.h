/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Score.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "../Engine/GameStateManager.h"


class Score : public GAM200::Component
{
public:
    Score() : scoreValue(0) {}

    void Add(int value);
    int Value() const;

private:
    int scoreValue;
};