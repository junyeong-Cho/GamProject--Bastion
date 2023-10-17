
#pragma once

#include "../Engine/GameStateManager.h"


class Life : public GAM200::Component
{
public:
    Life() : lifeValue(20) {}

    void Add(int value);
    void Subtract(int value);
    int Value() const;

private:
    int lifeValue;
};