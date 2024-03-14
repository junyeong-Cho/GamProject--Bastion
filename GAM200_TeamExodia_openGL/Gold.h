#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Gold : public GAM200::Component
{
public:
    Gold(int initial_gold) : gold(initial_gold) { }

    void Earn(int earn) { gold += earn; }
    void Spend(int spend) { gold -= spend; }

    int GetCurrentGold() const { return gold; }

private:
    int gold;
};

