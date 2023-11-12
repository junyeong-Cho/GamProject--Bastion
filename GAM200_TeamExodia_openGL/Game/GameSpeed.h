
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