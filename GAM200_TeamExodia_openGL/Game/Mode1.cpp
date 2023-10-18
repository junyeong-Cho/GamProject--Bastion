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



#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Collision.h"

#include "../Game/Mode1.h"
#include "../Game/States.h"
#include "../Game/Splash.h"
#include "../Game/Tile.h"
#include "../Game/Player.h"
#include "../Game/Monster.h"
#include "../Game/Tower.h"
#include "../Engine/DrawShape.h"

#include "Score.h"
#include "Gold.h"
#include "Life.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>

Mode1::Mode1() : player_ptr()
{

}


void Mode1::Load()
{
	

	counter = 0;

	AddGSComponent(new GAM200::GameObjectManager());

	AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));


	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	// 16:9
	int tile_col = 9;
	int tile_row = 16;
	int tile_size = window_size.x / tile_row;

	int map_info[9][16] = {
		static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile), static_cast<int>(GameObjectTypes::Passing_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
		static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile)
	};
	Math::irect map_positions[9][16];

	for (int y = 0; y < tile_col; ++y) {
		for (int x = 0; x < tile_row; ++x) {
			map_positions[y][x] = Math::irect{ { x * tile_size, y * tile_size }, { (x + 1) * tile_size, (y + 1) * tile_size } };
		}
	}

	for (int y = 0; y < tile_col; ++y) {
		for (int x = 0; x < tile_row; ++x) {
			switch (map_info[y][x]) {
			case static_cast<int>(GameObjectTypes::Passing_Tile):
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Passing_Tile(Math::irect{ map_positions[y][x] }));
				break;
			case static_cast<int>(GameObjectTypes::Block_Tile):
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Block_Tile(Math::irect{ map_positions[y][x] }));
				break;
			default:

				break;
			}
		}

	}
	
	Astar::GetInstance().UpdatePath(map_info, { 0, 0 }, { 5, 15 });

	player_ptr = new Player({ 0, 0 }, tile_size,128/2);
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);

	GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster({ 0, 0 }, player_ptr));
	//GetGSComponent <GAM200::GameObjectManager>()->Add(new Basic_Tower({ 0, 160 }));

	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });

	AddGSComponent(new Score());
	AddGSComponent(new Gold());
	AddGSComponent(new Life());

	#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
	#endif

	tower_offset = 0;
}

void Mode1::Update(double dt)
{
	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
	}

	if (GetGSComponent<Life>()->Value() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
	}

}

void Mode1::Unload()
{
	player_ptr = nullptr;
	//GetGSComponent<Background>()->Unload();
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void Mode1::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			m.Draw(480 * i, 270 * k, 480, 270);
		}

	}


	//Engine::GetWindow().Clear(0x000000FF);

	Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();

	//GetGSComponent<Background>()->Draw(*GetGSComponent<GAM200::Camera>());

	//timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 5 }));
	//score.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 80 }));

	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
	
	
	w.Draw(1200 - 150, 0, 150*2, 400*2);
}

void Mode1::ImguiDraw()
{
	/*ImGui::Begin("Program Info");
	{
		ImGui::Text("FPS: %f", "55.5");
		ImGui::Text("Frame Time: %f", "55.5");
		ImGui::Text("Counter: %f", counter);
		ImGui::Text("Player position: %.3f, %.3f", player_ptr->GetPosition().x, player_ptr->GetPosition().y);
		ImGui::Text("Camera position: %.3f, %.3f", GetGSComponent<GAM200::Camera>()->GetPosition().x, GetGSComponent<GAM200::Camera>()->GetPosition().y);

	}
	ImGui::End();*/


	ImGui::Begin("Informations");
	{
		/*ImGui::Text("Mouse Position X : %.2f", Engine::Instance().GetMouse().GetMousePosition().x);
		ImGui::Text("Mouse Position Y : %.2f", Engine::Instance().GetMouse().GetMousePosition().y);*/
		int gold = GetGSComponent<Gold>()->Value();
		int life = GetGSComponent<Life>()->Value();

		ImGui::Text("Killed Monster : %d", GetGSComponent<Score>()->Value());
		ImGui::Text("Gold : %d", gold);
		ImGui::Text("Life : %d", life);

		if (ImGui::SliderInt("Adjust Gold", &gold, 0, 600, "%d")) {
			GetGSComponent<Gold>()->SetValue(gold);
		}
		if (ImGui::SliderInt("Adjust Life", &life, 1, 30, "%d")) {
			GetGSComponent<Life>()->SetValue(life);
		}
	}
	ImGui::End();

	ImGui::Begin("Produec");
	{
		if (ImGui::Button("Produce Basic Monster"))
		{
			/*for (int i = 0; i < basic_monster_produce_number; i++) {
				Engine::GetLogger().LogDebug("Basic monster added\n");
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster({ 0, 0 }, player_ptr));
			}*/
			GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster({ 0, 0 }, player_ptr));
		}
		if (ImGui::Button("Produce Fast Monster"))
		{
			/*for (int i = 0; i < fast_monster_produce_number; i++) {	
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Fast_Monster({ 0, 0 }, player_ptr));
			}*/
			GetGSComponent<GAM200::GameObjectManager>()->Add(new Fast_Monster({ 0, 0 }, player_ptr));
		}

		static int size = 80;
		if (ImGui::Button("Produce Tower"))
		{
			if (GetGSComponent<Gold>()->Value() >= Basic_Tower::GetCost()) {
				GetGSComponent <GAM200::GameObjectManager>()->Add(new Basic_Tower({ static_cast<double>(tower_offset * size), 160 }));
				++tower_offset;
			}
		}
	}

	ImGui::End();
}

void Mode1::HandleEvent(SDL_Event& event)
{

}