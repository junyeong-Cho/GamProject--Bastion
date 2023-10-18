
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