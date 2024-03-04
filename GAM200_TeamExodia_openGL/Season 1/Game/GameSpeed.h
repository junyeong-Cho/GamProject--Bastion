/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameSpeed.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#pragma once

#include "../Engine/GameStateManager.h"


class GameSpeed : public GAM200::Component
{
public:
    GameSpeed(int max_speed = 3) : game_speed(1), max_speed(max_speed) {}

    void NextSpeed();
    int Value() const;
    int GetMax() const;
    void SetValue(int value) { game_speed = value; }

private:
    int game_speed;
    int max_speed;
};