/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Store.cpp
Project:    GAM200 Engine
Author:     Seunghun Kwon
Created:    March 14, 2024
*/

#include "Engine/Engine.h"
#include "Game/States.h"
#include "Game/Modes/Store.h"
#include "Game/Fonts.h"
#include "Game/Objects/Button.h"

#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"

#include "Engine/Audio.h"

#include "Component/Map.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>

extern int startGold;
int        diamond = 100;

extern int stock1;
extern int stock2;
extern int stock3;

extern int selected_stage;
extern int selected_map;

Store::Store()
{
}

void Store::Load()
{
	AddGSComponent(new GAM200::GameObjectManager());

	GAM200::GameObjectManager* gameobjectmanager = GetGSComponent<GAM200::GameObjectManager>();

	gameobjectmanager->Add(new Store_Menu_Button({ 18.6646, 745.1167 }, { 153, 43 }));
    gameobjectmanager->Add(new Store_GameStart_Button({ 1003.1398, 20.4109 }, { 257, 56 }));
    gameobjectmanager->Add(new Base_Item1_Button({ 125.2568, 121.9691 }, { 208, 206 }));
    gameobjectmanager->Add(new Base_Item2_Button({ 375.2568, 121.9691 }, { 208, 206 }));
    gameobjectmanager->Add(new Base_Item3_Button({ 625.2568, 121.9691 }, { 208, 206 }));
    gameobjectmanager->Add(new Selected_Stage0_Button({ 129.2302, 388.8858 }, { 100, 70 }));
    gameobjectmanager->Add(new Selected_Stage1_Button({ 247.6667, 388.8858 }, { 100, 70 }));
    gameobjectmanager->Add(new Selected_Stage2_Button({ 365.1032, 388.8858 }, { 100, 70 }));
    gameobjectmanager->Add(new Base_Map0_Button({ 610.9922, 492.9166 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map1_Button({ 319.4276, 551.8026 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map2_Button({ 542.6742, 475.5447 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map3_Button({ 952.8322, 570.4922 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map4_Button({ 237.3569, 577.3824 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map5_Button({ 610.9922, 496.4798 }, { 103.3583, 39.3964 }));
    gameobjectmanager->Add(new Base_Map6_Button({ 1004.6903, 588.7157 }, { 103.3583, 39.3964 }));

	counter = 0;

	store_background = Engine::Instance().GetTextureManager().Load("assets/Background/base_background.png");
    item_background  = Engine::Instance().GetTextureManager().Load("assets/Background/item_ui.png");
    base_cover       = Engine::Instance().GetTextureManager().Load("assets/Background/base_cover.png");
    base_stage0      = Engine::Instance().GetTextureManager().Load("assets/Background/base_stage0.png");
    base_stage1      = Engine::Instance().GetTextureManager().Load("assets/Background/base_stage1.png");
    base_stage2      = Engine::Instance().GetTextureManager().Load("assets/Background/base_stage2.png");

    #if !defined(__EMSCRIPTEN__)
	Engine::GetAudioManager().StopMusic(GAM200::AudioID::Game_BGM);
    #endif
}

void Store::Update(double dt)
{
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

    #if !defined(__EMSCRIPTEN__)
    if (!Engine::GetAudioManager().IsMusicPlaying(GAM200::AudioID::MainMenu_BGM))
    {
        Engine::GetAudioManager().PlayMusic(GAM200::AudioID::MainMenu_BGM);
    }
    #endif
}

void Store::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Store::Draw()
{
	store_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0 ,0 }));
    item_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    switch (selected_stage)
    {
        case 0: base_stage0->Draw(Math::TranslationMatrix(Math::vec2{ 112.5635, 376.3333 })); break;
        case 1: base_stage1->Draw(Math::TranslationMatrix(Math::vec2{ 112.5635, 376.3333 })); break;
        case 2: base_stage2->Draw(Math::TranslationMatrix(Math::vec2{ 112.5635, 376.3333 })); break;
    }

    base_cover->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

    ShaderDrawing::ShaderDraw::setFont("assets/font/Eina01-SemiBold.ttf");
    ShaderDrawing::draw_text(std::to_string(stock1), 315.1025 +   5, 800 - 524.8457, 15, 0.0f, 0.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(stock2), 315.1025 + 255, 800 - 524.8457, 15, 0.0f, 0.0f, 0.0f);
    ShaderDrawing::draw_text(std::to_string(stock3), 315.1025 + 505, 800 - 524.8457, 15, 0.0f, 0.0f, 0.0f);
    ShaderDrawing::ShaderDraw::setFont("assets/font/Eina01-Bold.ttf");
    ShaderDrawing::draw_text(std::to_string(diamond), 1120, 760, 20, 1.0f, 1.0f, 1.0f);
}

void Store::ImguiDraw()
{

}

void Store::HandleEvent(SDL_Event& event)
{

}
