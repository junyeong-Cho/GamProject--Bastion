/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Store.h
Project:    GAM200 Engine
Author:     Seunghun Kwon
Created:    March 14, 2024
*/

#pragma once


#include "Engine/GameState.h"
#include "Engine/Texture.h"

#include "Component/Gold.h"
#include "Game/Components/Life.h"
#include "Game/Objects/Button.h"

class Store : public GAM200::GameState
{
public:
    Store();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    void ImguiDraw() override;
    void HandleEvent(SDL_Event& event) override;

    std::string GetName() override { return "Store"; }

    enum class Difficulty
    {
        Easy,
        Normal,
        Hard,
        In_Game
    };

public:

    int counter = 0;
    std::unique_ptr<GAM200::Texture> gold;
    std::unique_ptr<GAM200::Texture> life;
    std::unique_ptr<GAM200::Texture> difficulty;

    GAM200::Texture* store_background;

    Math::vec2 mouse_position;
    Math::ivec2 tile_size;
};