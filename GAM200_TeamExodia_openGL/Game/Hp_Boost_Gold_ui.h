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

#include "../Engine/GameObject.h" 
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "../Engine/Texture.h"
#include "../Game/GameObjectTypes.h"

class Button;
class HBG_Ui : public GAM200::Component {
public:

    HBG_Ui(int hp, int gold, int boost);


    void Update();

    void Draw();



    GAM200::Texture HBG_BASE = GAM200::Texture("assets/images/ui/HBG/HBG_BASE.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture HP_EFFECT = GAM200::Texture("assets/images/ui/HBG/HP_EFFECT.png", GAM200::Texture::TextureType::RECTANGLE);
    GAM200::Texture HP_COVER = GAM200::Texture("assets/images/ui/HBG/HP_COVER.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture GOLD_COVER = GAM200::Texture("assets/images/ui/HBG/GOLD_COVER.png", GAM200::Texture::TextureType::RECTANGLE);

    GAM200::Texture BOOST_COVER = GAM200::Texture("assets/images/ui/HBG/BOOST_COVER.png", GAM200::Texture::TextureType::RECTANGLE);


    GAM200::Texture life = GAM200::Texture("assets/images/ui/HBG/hp_back.png", GAM200::Texture::TextureType::RECTANGLE);

    std::unique_ptr<GAM200::Texture>  remaining_gold;



    int Player_HP;
    int Tower_GOLD;
    int Player_BOOST;
    int aim_position;
    int wall_hp;
private:



    enum class Animations
    {
        Idle,
        Moving,
        Dashing,
        Skidding,
    };

    Button* w_button = nullptr;

    Button* basic_t_button = nullptr;
    Button* double_t_button = nullptr;
    Button* triple_t_button = nullptr;

    Button* delete_t_button = nullptr;
    Button* pass_t_button = nullptr;
    Button* block_t_button = nullptr;


    Button* choice_1_button = nullptr;
    Button* choice_2_button = nullptr;
    Button* choice_3_button = nullptr;


};

class HP : public HBG_Ui
{
public:
    void draw_hp();
    int hp_up_and_down();
private:

};

class GOLD : public HBG_Ui
{
public:
    void draw_gold();
    int gold_up_and_down();
private:

};


class BOOST : public HBG_Ui
{
public:
    void draw_boost();
    int boost_up_and_down();
private:

};