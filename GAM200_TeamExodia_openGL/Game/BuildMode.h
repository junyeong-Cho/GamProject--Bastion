
#pragma once

#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "GameObjectTypes.h"

#include "../Engine/GameObject.h" 
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Texture.h"
#include "../Game/GameObjectTypes.h"

class BuildMode : public GAM200::Component
{
public:
    BuildMode();

    void Update();
    void Draw();
    
    void Build(GameObjectTypes type);
    void DeleteTower();
    void ChangeTile(GameObjectTypes type);

    bool IsBuilding() const { return build_mode; }

    bool Click();

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


    bool four_way[4] = { false,false,false,false };
    bool empty_gold = false;
    bool tower_set_available = false;


private:
    bool build_mode = false;

    GameObjectTypes type;
    int cost = 0;

    Math::ivec2 mouse_tile_position;
    Math::ivec2 tile_size;

    Direction direction;


    ///
    Math::vec2 mouse_position;

    GAM200::Texture edit_1_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_1.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture edit_2_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_2.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture edit_2_up_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_2_up.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture edit_2_right_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_2_right.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture edit_2_down_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_2_down.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture edit_2_left_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_ui_2_left.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture edit_2_unable_aim = GAM200::Texture("assets/images/ui/tower_edit/tower_edit_2_unable.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture edit_2_unable_place_aim = GAM200::Texture("assets/images/ui/tower_edit/unable_place.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture change_aim = GAM200::Texture("assets/images/ui/tower_edit/change_aim.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture delete_aim = GAM200::Texture("assets/images/ui/tower_edit/delete_aim.png", GAM200::Texture::TextureType::RECTANGLE);
   
    GAM200::Texture obs_block = GAM200::Texture("assets/images/obs_block.png", GAM200::Texture::TextureType::RECTANGLE);
    
    ///
};