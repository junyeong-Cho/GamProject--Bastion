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


Store::Store()
{
	//Store_Gold = new Store_Gold_Button(Math::vec2(1120 - 40, 720 - 630), Math::vec2(180, 60));
}

void Store::Load()
{
	AddGSComponent(new GAM200::GameObjectManager());

	AddGSComponent(new Gold());
	AddGSComponent(new Life());

	AddGSComponent(new HBG_Ui());

    counter = 0;

	store_background = Engine::Instance().GetTextureManager().Load("assets/images/store_background.png");

	select1 = Engine::Instance().GetTextureManager().Load("assets/images/Select1.png");
	select2 = Engine::Instance().GetTextureManager().Load("assets/images/Select2.png");
	select3 = Engine::Instance().GetTextureManager().Load("assets/images/Select3.png");
	select4 = Engine::Instance().GetTextureManager().Load("assets/images/Select4.png");
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


	gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Gold :" + std::to_string(GetGSComponent<Gold>()->Value()), 0xFFFFFFFF));
	life.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Life :" + std::to_string(GetGSComponent<Life>()->Value()), 0xFFFFFFFF));
	//difficulty.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Difficulty :" + SelectedDifficulty(), 0xFFFFFFFF));
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



	//select1->Draw(Math::TranslationMatrix(Math::ivec2{ 100 ,Engine::GetWindow().GetSize().y/2 +60 }));
	//select2->Draw(Math::TranslationMatrix(Math::ivec2{ 400 ,Engine::GetWindow().GetSize().y / 2 +60}));
	//select3->Draw(Math::TranslationMatrix(Math::ivec2{ 700 ,Engine::GetWindow().GetSize().y / 2 +60}));
	//select4->Draw(Math::TranslationMatrix(Math::ivec2{ 1000 ,Engine::GetWindow().GetSize().y / 2 +60}));

	//menu->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 250 , 50 }));
	//game_start->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 450 , 50 }));

	gold->Draw(Math::TranslationMatrix(Math::ivec2{ 0, (Engine::GetWindow().GetSize().y) }));
	life->Draw(Math::TranslationMatrix(Math::ivec2{ 0, (Engine::GetWindow().GetSize().y - 60) }));
	//difficulty->Draw(Math::TranslationMatrix(Math::ivec2{ 300, (Engine::GetWindow().GetSize().y) }));
}

void Store::ImguiDraw()
{
	ImGui::Begin("Information");
	{
		int gold = GetGSComponent<Gold>()->Value();
		int life = GetGSComponent<Life>()->Value();

		ImGui::Text("Gold : %d", gold);
		ImGui::Text("Life : %d", life);

		if (ImGui::SliderInt("Adjust Gold", &gold, 0, 50000, "%d")) {
			GetGSComponent<Gold>()->SetValue(gold);
		}
		if (ImGui::SliderInt("Adjust Life", &life, 1, 500, "%d")) {
			GetGSComponent<Life>()->SetValue(life);
		}

	}
	ImGui::End();
}

void Store::HandleEvent(SDL_Event& event)
{

}



