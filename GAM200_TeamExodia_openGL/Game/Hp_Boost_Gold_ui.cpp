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

HBG_Ui::HBG_Ui(int hp, int gold, int boost) : Player_HP(hp), Tower_GOLD(gold), Player_BOOST(boost) {
    //AddGOComponent(new GAM200::Sprite("Assets/Player.spt", this));



}


void HBG_Ui::Update() {



    //remaining_gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("G: " + std::to_string(Tower_GOLD), 0xffffff));//화면 파랗게 만듬
}

void HBG_Ui::Draw() {
    GAM200::DrawShape shape;
    HBG_BASE.Draw(40, 605, 340, 80);
    HP_COVER.Draw(130, 720 - 60, Player_HP * 5, 15);
    BOOST_COVER.Draw(130, 720 - 78, Player_BOOST, 8);
    GOLD_COVER.Draw(130, 720 - 95, Tower_GOLD / 400, 5);

    //remaining_gold->Draw(Math::TranslationMatrix(Math::ivec2{ 130, 720 - 95 }));

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






