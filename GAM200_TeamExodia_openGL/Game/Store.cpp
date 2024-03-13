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

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>
#include <imgui_impl_sdl.h>
#include "../Season 1/Game/Gold.h"
#include "../Season 1/Game/Life.h"

Store::Store()
{

}

void Store::Load()
{
	AddGSComponent(new GAM200::GameObjectManager());

	AddGSComponent(new Gold());
	AddGSComponent(new Life());

    counter = 0;
	texture1 = Engine::Instance().GetTextureManager().Load("assets/images/test1.png");
	texture2 = Engine::Instance().GetTextureManager().Load("assets/images/test2.png");
	gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold :", 0xFFFFFFFF));
	life.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("life :", 0xFFFFFFFF));
}

void Store::Update(double dt)
{

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}

	if (Engine::GetInput().KeyJustPressed(GAM200::Input::Keys::Enter))
	{
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}

}

void Store::Unload()
{
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Store::Draw()
{
	Engine::GetWindow().Clear(0.5, 0.5, 0.5, 1.0);

	texture1->Draw(Math::TranslationMatrix(Math::ivec2{ 150 ,Engine::GetWindow().GetSize().y/4 }));
	texture2->Draw(Math::TranslationMatrix(Math::ivec2{ 500 ,Engine::GetWindow().GetSize().y / 4 }));
	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 0, (Engine::GetWindow().GetSize().y) }));
	life->Draw(Math::TranslationMatrix(Math::ivec2{ 0, (Engine::GetWindow().GetSize().y - 60) }));
}

void Store::ImguiDraw()
{
	ImGui::Begin("Information");
	{
		//int gold = GetGSComponent<Gold>()->Value();
		//int life = GetGSComponent<Life>()->Value();
		//int gold = 100000;
		//int life = 500;

		//int set_gold = 0;
		//int set_life = 0;

		//ImGui::Text("Gold : %d", gold);
		//ImGui::Text("Life : %d", life);


		//if (ImGui::SliderInt("Adjust Gold", &gold, 0, 100000, "%d")) {
		//	GetGSComponent<Gold>()->SetValue(gold);
		//	//set_gold = gold;
		//}
		//if (ImGui::SliderInt("Adjust Life", &life, 1, 500, "%d")) {
		//	GetGSComponent<Life>()->SetValue(life);
		//	//set_life = life;
		//}

	}
	ImGui::End();
}

void Store::HandleEvent(SDL_Event& event)
{

}