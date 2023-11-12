
#pragma once

#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "GameObjectTypes.h"

class BuildMode : public GAM200::Component
{
public:
    BuildMode();

    void Update();
    void Draw();
    void Build(GameObjectTypes type);

    enum Direction
    {
        RIGHT, LEFT, UP, DOWN
    };

private:
    bool build_mode;

    GameObjectTypes tower_type = GameObjectTypes::Basic_Tower;
    int cost = 0;

    Math::ivec2 mouse_tile_position;
    Math::ivec2 tile_size;

    Direction direction;
};