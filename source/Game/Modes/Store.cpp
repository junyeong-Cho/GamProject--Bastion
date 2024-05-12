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


#include <filesystem>
#include <imgui.h>
#include <stb_image.h>

extern int startGold;
int        diamond = 100;

Store::Store()
{
}

void Store::Load()
{
	AddGSComponent(new GAM200::GameObjectManager());

	GAM200::GameObjectManager* gameobjectmanager = GetGSComponent<GAM200::GameObjectManager>();
	gameobjectmanager->Add(new Store_Easy_Button({ 100, 420 }, { 200, 150 }));
	gameobjectmanager->Add(new Store_Normal_Button({ 400, 420 }, { 200, 150 }));
	gameobjectmanager->Add(new Store_Hard_Button({ 700, 420 }, { 200, 150 }));

	gameobjectmanager->Add(new Store_Item_1({ 100, 140 }, { 200, 150 }));
    gameobjectmanager->Add(new Store_Item_2({ 400, 140 }, { 200, 150 }));
    gameobjectmanager->Add(new Store_Item_3({ 700, 140 }, { 200, 150 }));

	gameobjectmanager->Add(new Store_Tutorial_Button({ 1000, 420 }, { 200, 150 }));
	gameobjectmanager->Add(new Store_Menu_Button({ 1030, 50 }, { 200, 150 }));
	

	counter = 0;

	store_background = Engine::Instance().GetTextureManager().Load("assets/Background/store_background.png");

    GAM200::SoundEffect::MainMenu_BGM().stopAll();
    GAM200::SoundEffect::Game_BGM().stopAll();
    GAM200::SoundEffect::MainMenu_BGM().loopplay();
}

void Store::Update(double dt)
{
	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

	if(Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::P))
	{
        startGold += 50;
	}
}

void Store::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Store::Draw()
{
	store_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0 ,0 }));
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

	ShaderDrawing::draw_text("Gold: " + std::to_string(diamond), 1100, 700, 50, 1.0f, 1.0f, 0.0f);
}

void Store::ImguiDraw()
{

}

void Store::HandleEvent(SDL_Event& event)
{

}
