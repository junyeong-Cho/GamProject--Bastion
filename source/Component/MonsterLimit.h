#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

#include "Game/Objects/Monsters/Monster.h"

class MonsterLimit : public GAM200::Component
{
public:
    MonsterLimit(int max_limit) : max_limit(max_limit) { }
    int GetCurrentMonster() const { return Monster::GetRemainingMonster(); }
    int GetLimit() const { return max_limit; }

    int SetLimit(int new_limit)
    {
        max_limit = new_limit;
    }
    bool GameOver() const { return Monster::GetRemainingMonster() >= max_limit ? true : false; }

private:
    int max_limit;
};

