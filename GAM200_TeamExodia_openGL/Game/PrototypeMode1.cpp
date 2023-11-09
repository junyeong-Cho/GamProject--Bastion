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
#include "../Map.h"

#include "../Game/PrototypeMode1.h"
#include "../Game/States.h"
#include "../Game/PrototypeSplash.h"
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
#include "../Engine/Audio.h"

PrototypeMode1::PrototypeMode1() : player_ptr()
{

}


void PrototypeMode1::Load()
{
	// Music
	AddGSComponent(new GAM200::MusicEffect());
	GetGSComponent<GAM200::MusicEffect>()->LoadFile("assets/Sounds/Theme/example_music.ogg");

	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());
	// Camera
	AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));
	// Window, tiles
	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	int tile_col = 9;
	int tile_row = 16;
	int tile_size = window_size.x / tile_row;
	// Set Map
	Map::GetInstance().SetMap1();
	map_info = Map::GetInstance().GetMap();
	// Need to change to a function!!!!!!!!!!!!!!
	for (int y = 0; y < tile_col; ++y) {
		for (int x = 0; x < tile_row; ++x) {
			switch (map_info[y][x]) {
			case static_cast<int>(GameObjectTypes::Pass__Tile):
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Pass__Tile(Math::irect{ { x * tile_size, y * tile_size }, { (x + 1) * tile_size, (y + 1) * tile_size } }));
				break;
			case static_cast<int>(GameObjectTypes::Block_Tile):
				GetGSComponent<GAM200::GameObjectManager>()->Add(new Block_Tile(Math::irect{ { x * tile_size, y * tile_size }, { (x + 1) * tile_size, (y + 1) * tile_size } }));
				break;
			default:

				break;
			}
		}

	}
	// Set Path using AStar
	Astar::GetInstance().UpdatePath(map_info, { 0, 0 }, { 8, 13 });
	// Add Player
	player_ptr = new Player({ 0, 0 }, tile_size*2/3, tile_size*2/3);
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);
	// Camera Setting
	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });
	// Informations
	AddGSComponent(new Score());
	AddGSComponent(new Gold());
	AddGSComponent(new Life());

	#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
	#endif

	tower_offset = 0;
}

void PrototypeMode1::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tab)) {
		switch (game_speed) {
		case 1:
			game_speed = 2;
			break;
		case 2:
			game_speed = 3;
			break;
		case 3:
			game_speed = 1;
			break;
		}
	}
	dt *= static_cast<double>(game_speed);

	GetGSComponent<GAM200::MusicEffect>()->Play(0);

	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	//GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
		GetGSComponent<GAM200::MusicEffect>()->Stop();
	}

	if (GetGSComponent<Life>()->Value() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
		GetGSComponent<GAM200::MusicEffect>()->Stop();
	}

}

void PrototypeMode1::Unload()
{
	player_ptr = nullptr;
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void PrototypeMode1::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			m.Draw(480 * i, 270 * k, 480, 270);
		}

	}

	Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();

	//GetGSComponent<Background>()->Draw(*GetGSComponent<GAM200::Camera>());

	//timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 5 }));
	//score.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 80 }));

	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);
	
	
	w.Draw(1200 - 150, 0, 150*2, 400*2);
}

void PrototypeMode1::ImguiDraw()
{
	ImGui::Begin("Information");
	{
		int gold = GetGSComponent<Gold>()->Value();
		int life = GetGSComponent<Life>()->Value();
		int score = GetGSComponent<Score>()->Value();

		ImGui::Text("Killed Monster : %d", score);
		ImGui::Text("Gold : %d", gold);
		ImGui::Text("Life : %d", life);
		ImGui::Text("Game Speed : %d", game_speed);

		if (ImGui::SliderInt("Adjust Gold", &gold, 0, 600, "%d")) {
			GetGSComponent<Gold>()->SetValue(gold);
		}
		if (ImGui::SliderInt("Adjust Life", &life, 1, 30, "%d")) {
			GetGSComponent<Life>()->SetValue(life);
		}

		if (ImGui::SliderInt("Adjust Game Speed", &game_speed, 1, 3, "%d")) {
			Engine::GetLogger().LogEvent("Game Speed: x" + std::to_string(game_speed));
		}
	}
	ImGui::End();


	ImGui::Begin("Produec");
	{
		if (ImGui::Button("Produce Basic Monster"))
		{
			GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster({ 0, 0 }, player_ptr));
		}
		if (ImGui::Button("Produce Fast Monster"))
		{
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


	ImGui::Begin("Music Info");
	{

		float* musicVolume = (GetGSComponent<GAM200::MusicEffect>()->GetMusicVolume());

		if (ImGui::SliderFloat("Max Volume", musicVolume, 0.0f, 100.0f, "%.0f"))
		{
			GetGSComponent<GAM200::MusicEffect>()->SetVolume(*musicVolume);
		}


	}
	ImGui::End();

}

void PrototypeMode1::HandleEvent(SDL_Event& event)
{

}