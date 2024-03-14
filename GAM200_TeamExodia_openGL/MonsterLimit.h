#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class MonsterLimit : public GAM200::Component
{
public:
    MonsterLimit(int max_limit) : max_limit(max_limit) { }

    int GetCurrentMonster() const { return current_monsters; }
    int GetLimit() const { return max_limit; }

private:
    int current_monsters = 0;
    int max_limit;
};

