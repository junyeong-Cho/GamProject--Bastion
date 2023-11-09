/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Player.h
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    October		10, 2023
*/

#pragma once

#include "IProgram.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/Camera.h"
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "GameObjectTypes.h"


class Player;

class PrototypeMode1 : public GAM200::GameState
{
public:
    PrototypeMode1();
    void Load()                                  override;
    void Update(double dt)                       override;
    void Unload()                                override;
    void Draw()                                  override;

    void ImguiDraw()                             override;
    void HandleEvent(SDL_Event& event)           override;




    std::string GetName() override { return "PrototypeMode1"; }
public:

    double counter = 0;

    int x = 0;
    int y = 0;
    int velocity = 500;

    Player* player_ptr;

    int game_speed = 1;

    //int basic_monster_produce_number = 1;
    //int fast_monster_produce_number = 1;

private:

    GAM200::Texture m = GAM200::Texture("assets/images/m.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture w = GAM200::Texture("assets/images/w.png", GAM200::Texture::TextureType::RECTANGLE);

    int map_info[9][16] = {
        static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
        static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile)
    };

    int tower_offset = 0;
};
