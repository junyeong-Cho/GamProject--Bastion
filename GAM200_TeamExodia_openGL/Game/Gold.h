
#pragma once

#include "../Engine/GameStateManager.h"


class Gold : public GAM200::Component
{
public:
    Gold() : goldValue(100000) {}

    void Add(int value);
    void Subtract(int value);
    int Value() const;

private:
    int goldValue;
};