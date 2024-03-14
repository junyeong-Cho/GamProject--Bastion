#pragma once

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

#include "../Engine/Input.h"

class GameSpeed : public GAM200::Component
{
public:
    GameSpeed() { }

    double GetSpeed() const { return speed; }

    void NextSpeed() { (speed == 4) ? (speed = 1) : (++speed); }

private:
    double speed = 1;
};
