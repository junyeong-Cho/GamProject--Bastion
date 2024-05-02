/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Store.cpp
Project:    GAM200 Engine
Author:     Seunghun Kwon
Created:    March 14, 2024
*/

#include "../Engine/Engine.h"
#include "../Game/States.h"
#include "../Game/Store.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"
#include "Fonts.h"
#include "../Game/Button.h"


#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>
#include <imgui_impl_sdl.h>


Store::Store()
{
}

void Store::Load()
{
	AddGSComponent(new GAM200::GameObjectManager());



	GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_Easy_Button({ 100, 420 }, { 200, 150 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_Normal_Button({ 400, 420 }, { 200, 150 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_Hard_Button({ 700, 420 }, { 200, 150 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_Tutorial_Button({ 1000, 420 }, { 200, 150 }));
	//GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_InGame_Button({ 1000, 420 }, { 200, 150 }));
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Store_Menu_Button({ 1030, 50 }, { 200, 150 }));

    counter = 0;

	store_background = Engine::Instance().GetTextureManager().Load("assets/Background/store_background.png");
}

void Store::Update(double dt)
{

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);


	
}

void Store::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Store::Draw()
{
	//Engine::GetWindow().Clear(0.5, 0.5, 0.5, 1.0);
	store_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0 ,0 }));
	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
}

void Store::ImguiDraw()
{
	
}

void Store::HandleEvent(SDL_Event& event)
{

}



