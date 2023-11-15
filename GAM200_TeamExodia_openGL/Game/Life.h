
#pragma once

#include "../Engine/GameStateManager.h"


class Life : public GAM200::Component
{
public:
    Life() : lifeValue(50) {}

    void Add(int value);
    void Subtract(int value);
    int Value() const;
    void SetValue(int value) { lifeValue = value; }

private:
    int lifeValue;
};