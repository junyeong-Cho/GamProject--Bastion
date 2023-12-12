
#pragma once

#include "../Engine/GameStateManager.h"


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

private:
    int goldValue;

    double interest_rate = 0.2;
};