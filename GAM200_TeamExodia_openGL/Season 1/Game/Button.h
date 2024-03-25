/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Button.h
Project:    GAM200 Engine
Author:     Hyeonjoon Nam
Created:    November 2, 2023
Updated:    December 15, 2023
*/

#pragma once


#include "../Engine/GameStateManager.h"
#include "../Engine/Vec2.h"
#include "../Game/GameObjectTypes.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "Wave.h"


class Button : public GAM200::GameObject
{
public:
    Button(Math::vec2 position, Math::vec2 size);

    GameObjectTypes Type() override { return GameObjectTypes::Button; }
    std::string TypeName() override { return "Button"; }

    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

    virtual bool IsClicked();

    //bool tower_type[7] = { false,false,false, false,false,false,false };//basic doble triple delete change_tp change_tb wave
    bool stage[2] = { false, false }; //Store Game
protected:
    virtual void func();
    //bool is_activated = true;
private:
    GAM200::Texture store_easy = GAM200::Texture("assets/images/Select1.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_normal = GAM200::Texture("assets/images/Select2.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_hard = GAM200::Texture("assets/images/Select3.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_ingame = GAM200::Texture("assets/images/Select4.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_gold = GAM200::Texture("assets/images/test1.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_life = GAM200::Texture("assets/images/test2.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_game_start = GAM200::Texture("assets/images/game_start.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture store_menu = GAM200::Texture("assets/images/menu.png", GAM200::Texture::TextureType::RECTANGLE);


    Math::vec2 position;
    Math::vec2 size;

    Math::vec2 mouse_position;

    bool is_on = false;
};

class Store_Easy_Button : public Button {
public:
    Store_Easy_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Normal_Button : public Button {
public:
    Store_Normal_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Hard_Button : public Button {
public:
    Store_Hard_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_InGame_Button : public Button {
public:
    Store_InGame_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Gold_Button : public Button {
    public:
    Store_Gold_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Life_Button : public Button {
public:
    Store_Life_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_Menu_Button : public Button {
public:
    Store_Menu_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

class Store_GameStart_Button : public Button {
public:
    Store_GameStart_Button(Math::vec2 position, Math::vec2 size);

    void func() override;
};

