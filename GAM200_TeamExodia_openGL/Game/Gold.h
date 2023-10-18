
#pragma once

#include "../Engine/GameStateManager.h"


class Gold : public GAM200::Component
{
public:
    Gold() : goldValue(0) {}

    void Add(int value);
    void Subtract(int value);
    int Value() const;
    void SetValue(int value) { goldValue = value; }

private:
    int goldValue;
};