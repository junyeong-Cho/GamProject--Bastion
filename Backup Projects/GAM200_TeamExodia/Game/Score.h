/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Score.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/


#pragma once

#include "../Engine/GameStateManager.h"


class Score : public CS230::Component
{
public:
    Score() : scoreValue(0) {}

    void Add(int value);
    int Value() const;

private:
    int scoreValue;
};