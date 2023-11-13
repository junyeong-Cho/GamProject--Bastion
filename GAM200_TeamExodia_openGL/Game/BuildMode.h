
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
    void DeleteTower();
    void ChangeTile(GameObjectTypes type);

    enum Direction
    {
        RIGHT, LEFT, UP, DOWN
    };
    enum Mode
    {
        CHANGE_TILE,

        DELETE_TOWER,
        BUILD_TOWER
    } mode;

private:
    bool build_mode;

    GameObjectTypes type;
    int cost = 0;

    Math::ivec2 mouse_tile_position;
    Math::ivec2 tile_size;

    Direction direction;
};