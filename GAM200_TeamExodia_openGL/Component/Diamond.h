#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Diamond : public GAM200::Component
{
public:
    Diamond(int initial_diamond) : diamond(initial_diamond) { }

    void Earn(int earn) { diamond += earn; }
    void Spend(int spend) { diamond -= spend; }

    int GetCurrentDiamond() const { return diamond; }

private:
    int diamond;
};
