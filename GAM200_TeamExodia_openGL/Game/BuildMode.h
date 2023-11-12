
#pragma once

#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"


class BuildMode : public GAM200::Component
{
public:
    BuildMode();

    void Update();
    void Draw();
    void Build() { build_mode = true; }

    enum Direction
    {
        RIGHT, LEFT, UP, DOWN
    };

private:
    bool build_mode;

    Math::ivec2 mouse_tile_position;
    Math::ivec2 tile_size;

    Direction direction;
};