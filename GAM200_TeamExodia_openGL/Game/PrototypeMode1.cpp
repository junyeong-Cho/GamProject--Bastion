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
#include "../GameSpeed.h"

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

	// Set Map
	PrototypeMode1::SetMap("assets/maps/Map2.txt");

	// Add Player
	player_ptr = new Player({ 0, 0 }, tile_size_x * 2 / 3, tile_size_y * 2 / 3);
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);

	// Camera Setting
	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });

	// Informations
	AddGSComponent(new Score());
	AddGSComponent(new Gold());
	AddGSComponent(new Life());
	AddGSComponent(new GameSpeed(5));	// Parameter is for the max game speed

	#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
	#endif

	tower_offset = 0;
}

void PrototypeMode1::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tab)) 
	{
		GetGSComponent<GameSpeed>()->NextSpeed();
	}
	dt *= static_cast<double>(GetGSComponent<GameSpeed>()->Value());

	GetGSComponent<GAM200::MusicEffect>()->Play(0);

	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();


	#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
	#endif
	
	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

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
	Map::GetInstance().MapUnload();
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
		int game_speed = GetGSComponent<GameSpeed>()->Value();
		int max_speed = GetGSComponent<GameSpeed>()->GetMax();
		float* musicVolume = (GetGSComponent<GAM200::MusicEffect>()->GetMusicVolume());

		ImGui::Text("Killed Monster : %d", score);
		ImGui::Text("Gold : %d", gold);
		ImGui::Text("Life : %d", life);
		ImGui::Text("Game Speed : %d", game_speed);

		////////// Mouse tile info ////////////
		Math::ivec2 window_size = Engine::GetWindow().GetSize();
		int tile_col = Map::GetInstance().GetSize().x;
		int tile_row = Map::GetInstance().GetSize().y;
		int tile_size_x = window_size.x / tile_row;
		int tile_size_y = window_size.y / tile_col;

		Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();
		Math::ivec2 mouse_tile_position = Math::ivec2(static_cast<int>(mouse_position.x / tile_size_x), static_cast<int>(mouse_position.y / tile_size_y));

		ImGui::Text("Current Tile Info : %d, %d", mouse_tile_position.x, mouse_tile_position.y);
		////////////////////////////////////////

		if (ImGui::SliderInt("Adjust Gold", &gold, 0, 600, "%d")) {
			GetGSComponent<Gold>()->SetValue(gold);
		}
		if (ImGui::SliderInt("Adjust Life", &life, 1, 30, "%d")) {
			GetGSComponent<Life>()->SetValue(life);
		}
		if (ImGui::SliderInt("Adjust Game Speed", &game_speed, 0, max_speed, "%d")) {
			GetGSComponent<GameSpeed>()->SetValue(game_speed);
		}

		if (ImGui::SliderFloat("Max Volume", musicVolume, 0.0f, 100.0f, "%.0f"))
		{
			GetGSComponent<GAM200::MusicEffect>()->SetVolume(*musicVolume);
		}
	}
	ImGui::End();


	ImGui::Begin("Produce");
	{
		if (ImGui::Button("Produce Basic Monster"))
		{
			Engine::GetLogger().LogEvent("Basic Monster Produce!");
			GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster({ 0, 0 }, player_ptr));
		}
		if (ImGui::Button("Produce Fast Monster"))
		{
			Engine::GetLogger().LogEvent("Fast Monster Produce!");
			GetGSComponent<GAM200::GameObjectManager>()->Add(new Fast_Monster({ 0, 0 }, player_ptr));
		}


		if (ImGui::Button("Produce Tower"))
		{
			if (GetGSComponent<Gold>()->Value() >= Basic_Tower::GetCost()) {
				GetGSComponent <GAM200::GameObjectManager>()->Add(new Basic_Tower({ static_cast<double>(tower_offset * tile_size_x), tile_size_y * 3.0 }));
				++tower_offset;
			}
		}


	}
	ImGui::End();


}

void PrototypeMode1::HandleEvent(SDL_Event& event)
{

}


void PrototypeMode1::SetMap(std::string file_name) 
{
	// Set Map
	Map::GetInstance().SetMap(file_name);

	// Window, tiles
	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	tile_col = Map::GetInstance().GetSize().x;
	tile_row = Map::GetInstance().GetSize().y;
	tile_size_x = window_size.x / tile_row;
	tile_size_y = window_size.y / tile_col;

	Astar::GetInstance().UpdatePath(Map::GetInstance().GetMap(), Map::GetInstance().GetStartPoint(), Map::GetInstance().GetEndPoint());
}


void PrototypeMode1::ChangeTile(Math::ivec2 position, GameObjectTypes type) {
	Map::GetInstance().ChangeTile(position, type);

	int cols = position.y;
	int rows = position.x;

	
	GetGSComponent<GAM200::GameObjectManager>()->Add(new Pass__Tile(Math::irect{ { rows * tile_size_x, cols * tile_size_y }, { (rows + 1) * tile_size_x, (cols + 1) * tile_size_y } }));
}