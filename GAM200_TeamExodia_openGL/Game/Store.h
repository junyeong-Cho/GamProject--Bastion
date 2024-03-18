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


#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

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

    virtual bool IsClicked(int x1, int y1, int x2, int y2);

    std::string GetName() override { return "Store"; }

    enum class Difficulty
    {
        Easy,
        Normal,
        Hard,
        In_Game
    };

public:

    double counter = 0;
    std::unique_ptr<GAM200::Texture> gold;
    std::unique_ptr<GAM200::Texture> life;
    std::unique_ptr<GAM200::Texture> difficulty;

    GAM200::Texture* texture1;
    GAM200::Texture* texture2;

    GAM200::Texture* select1;
    GAM200::Texture* select2;
    GAM200::Texture* select3;
    GAM200::Texture* select4;

    GAM200::Texture* menu;

    Math::vec2 mouse_position;
    Math::ivec2 tile_size;

    bool is_on = false;
};