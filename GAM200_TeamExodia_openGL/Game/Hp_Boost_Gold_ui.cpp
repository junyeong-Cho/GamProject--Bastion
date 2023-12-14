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

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"
#include "../Engine/GameObjectManager.h"

#include "Hp_Boost_Gold_ui.h"//
#include "Mode1.h"
#include "States.h"
#include "Bullet.h"
#include "Monster.h"
#include "Fonts.h"
#include "../Engine/Mouse.h"
#include "Timer.h"

#include "Button.h"
#include "Map.h"

HBG_Ui::HBG_Ui(int hp, int gold, int boost) : Player_HP(hp), Tower_GOLD(gold), Player_BOOST(boost) {
    //AddGOComponent(new GAM200::Sprite("Assets/Player.spt", this));

    if (Map::GetInstance().editor_mode == false)
    {
        w_button = new Wave_Start_Button(Math::vec2(1120 - 40, 720 - 630), Math::vec2(180, 60));

        basic_t_button = new Basic_Tower_Button(Math::vec2(1120, 720 - 150), Math::vec2(140, 70));
        double_t_button = new Double_Tower_Button(Math::vec2(1120, 720 - 230), Math::vec2(140, 70));
        triple_t_button = new Triple_Tower_Button(Math::vec2(1120, 720 - 310), Math::vec2(140, 70));

        delete_t_button = new Delete_Tower_Button(Math::vec2(1120, 720 - 390), Math::vec2(140, 70));
        pass_t_button = new Pass_Tile_Button(Math::vec2(1120, 720 - 470), Math::vec2(140, 70));
        block_t_button = new Block_Tile_Button(Math::vec2(1120, 720 - 550), Math::vec2(140, 70));


        choice_1_button = new Choice_1_Button(Math::vec2(50, 100), Math::vec2(300, 500));
        choice_2_button = new Choice_2_Button(Math::vec2(400, 100), Math::vec2(300, 500));
        choice_3_button = new Choice_3_Button(Math::vec2(750, 100), Math::vec2(300, 500));

    }

}


void HBG_Ui::Update() {



    remaining_gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("G: " + std::to_string(Tower_GOLD), 0xffffff));
}

void HBG_Ui::Draw() {
    GAM200::DrawShape shape;
    HBG_BASE.Draw(40, 605, 340, 80);
    HP_COVER.Draw(130, 720 - 60, Player_HP * 25 / 2, 15);
    BOOST_COVER.Draw(130, 720 - 78, Player_BOOST * 50, 8);
    GOLD_COVER.Draw(130, 720 - 95, Tower_GOLD / 400, 5);

    //remaining_gold->Draw(Math::TranslationMatrix(Math::ivec2{ 130, 720 - 95 }));
    life.Draw(390, 30, 500, 15);
    HP_COVER.Draw(390, 30, wall_hp * 10, 15);

    if (Map::GetInstance().editor_mode == false)
    {
        w_button->Draw(Math::TransformationMatrix());

        basic_t_button->Draw(Math::TransformationMatrix());
        double_t_button->Draw(Math::TransformationMatrix());
        triple_t_button->Draw(Math::TransformationMatrix());

        delete_t_button->Draw(Math::TransformationMatrix());
        pass_t_button->Draw(Math::TransformationMatrix());
        block_t_button->Draw(Math::TransformationMatrix());

        choice_1_button->Draw(Math::TransformationMatrix());
		choice_2_button->Draw(Math::TransformationMatrix());
        choice_3_button->Draw(Math::TransformationMatrix());
    }
}

void HP::draw_hp()
{

}

int HP::hp_up_and_down()
{
    return 0;
}





void GOLD::draw_gold()
{

}

int GOLD::gold_up_and_down()
{
    return 0;
}





void BOOST::draw_boost()
{

}

int BOOST::boost_up_and_down()
{
    return 0;
}




