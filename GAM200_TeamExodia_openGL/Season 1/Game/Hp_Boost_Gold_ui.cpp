/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Hp_Boost_Gold_ui.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    October		10, 2023
Updated:    December	15, 2023
*/

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"
#include "../Engine/GameObjectManager.h"

#include "Hp_Boost_Gold_ui.h"


HBG_Ui::HBG_Ui() {
    store_easy = new Store_Easy_Button(Math::vec2(100, 420), Math::vec2(200, 150));
    store_normal = new Store_Normal_Button(Math::vec2(400, 420), Math::vec2(200, 150));
    store_hard = new Store_Hard_Button(Math::vec2(700, 420), Math::vec2(200, 150));
    store_ingame = new Store_InGame_Button(Math::vec2(1000, 420), Math::vec2(200, 150));
    store_gold = new Store_Gold_Button(Math::vec2(100, 180), Math::vec2(200, 100));
    store_life = new Store_Life_Button(Math::vec2(350, 180), Math::vec2(200, 100));
    store_menu = new Store_Menu_Button(Math::vec2(1030, 50), Math::vec2(200, 150));
    store_game_start = new Store_GameStart_Button(Math::vec2(830, 50), Math::vec2(200, 150));

}


void HBG_Ui::Update() {

}

void HBG_Ui::Draw() {
    GAM200::DrawShape shape;

    store_easy->Draw(Math::TransformationMatrix());
    store_normal->Draw(Math::TransformationMatrix());
    store_hard->Draw(Math::TransformationMatrix());
    store_ingame->Draw(Math::TransformationMatrix());
    store_gold->Draw(Math::TransformationMatrix());
    store_life->Draw(Math::TransformationMatrix());
    store_menu->Draw(Math::TransformationMatrix());
    store_game_start->Draw(Math::TransformationMatrix());
}


