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
#include "Map.h"

#include "../Game/GamePlayEditor.h"
#include "../Game/States.h"
#include "../Game/PrototypeSplash.h"
#include "../Game/Tile.h"
#include "../Game/Player.h"
#include "../Game/Monster.h"
#include "../Game/Tower.h"
#include "../Game/ShowPath.h"
#include "../Engine/DrawShape.h"

#include "Score.h"
#include "Gold.h"
#include "Life.h"
#include "GameSpeed.h"
#include "Wave.h"
#include "BuildMode.h"
#include "Button.h"

#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>
#include "../Engine/Audio.h"
#include "ModeSelect.h"


GamePlayEditor::GamePlayEditor() : player_ptr()
{

}

void GamePlayEditor::Load()
{
	GAM200::SoundEffect::MainMenu_BGM().stopAll();


	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// Camera
	AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));

	// Set Map
	GamePlayEditor::SetMap("assets/maps/editor.txt");

	// Add Player
	player_ptr = new Player({ 0, 0 }, tile_size.x * 2 / 3, tile_size.y * 2 / 3);
	GetGSComponent<GAM200::GameObjectManager>()->Add(player_ptr);

	// Camera Setting
	GetGSComponent<GAM200::Camera>()->SetPosition({ 0, 0 });

	// Informations
	AddGSComponent(new Score());
	AddGSComponent(new Gold());
	AddGSComponent(new Life());
	AddGSComponent(new GameSpeed(3));	// Parameter is for the max game speed
	AddGSComponent(new Wave());
	GetGSComponent<Wave>()->SetWave();
	AddGSComponent(new BuildMode());
	AddGSComponent(new ShowPath());

	// add HBG Ui
	AddGSComponent(new HBG_Ui(50, 0, 0));

	Math::ivec2 size = Math::ivec2(Map::GetInstance().GetSize().y, Map::GetInstance().GetSize().x);

	// Monster Initalize
	MonsterFactory::InitBasicMonsterFromFile();
	MonsterFactory::InitFastMonsterFromFile();
	MonsterFactory::InitSlowMonsterFromFile();
	MonsterFactory::InitWeakMonsterFromFile();
	MonsterFactory::InitMotherMonsterFromFile();
	MonsterFactory::InitHealMonsterFromFile();
	MonsterFactory::InitStealthMonsterFromFile();

	// Tower Initialize
	TowerFactory::InitBasicTowerFromFile();
	TowerFactory::InitDoubleTowerFromFile();
	TowerFactory::InitTripleTowerFromFile();
	TowerFactory::InitPushTowerFromFile();
	TowerFactory::InitWideTowerFromFile();


#ifdef _DEBUG
	AddGSComponent(new GAM200::ShowCollision());
#endif

}

void GamePlayEditor::Update(double dt)
{
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tab))
	{
		GetGSComponent<GameSpeed>()->NextSpeed();
	}
	dt *= static_cast<double>(GetGSComponent<GameSpeed>()->Value());

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Click_Handle();


	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();

	GetGSComponent<Wave>()->Update(dt);

	//GetGSComponent<BuildMode>()->Update();

	GetGSComponent<ShowPath>()->Update();


#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
#endif

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}

	if (GetGSComponent<Life>()->Value() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Lose));
	}

	int gold = GetGSComponent<Gold>()->Value();
	int score = GetGSComponent<Score>()->Value();
	int player_hp = player_ptr->GetHP();
	int main_hp = GetGSComponent<Life>()->Value();

	GetGSComponent<HBG_Ui>()->Player_BOOST = 0;
	GetGSComponent<HBG_Ui>()->wall_hp = main_hp;
	GetGSComponent<HBG_Ui>()->Player_HP = player_hp;
	GetGSComponent<HBG_Ui>()->Tower_GOLD = gold;

	//Tower_Adopter::GetInstance().Show_Info();
}

void GamePlayEditor::Unload()
{
	player_ptr = nullptr;
	Map::GetInstance().MapUnload();
	Monster::remaining_monsters = 0;
	GetGSComponent<GAM200::GameObjectManager>()->Unload();
	ClearGSComponent();
}

void GamePlayEditor::Draw()
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

	GetGSComponent<ShowPath>()->DrawPath();

	GetGSComponent<BuildMode>()->Draw();
	player_ptr->Draw(camera_matrix);
	GetGSComponent<HBG_Ui>()->Draw();
}

void GamePlayEditor::ImguiDraw()
{
	if (Map::GetInstance().editor_mode == false)
		return;

	ImGui::Begin("Information");
	{
		int gold = GetGSComponent<Gold>()->Value();
		int life = GetGSComponent<Life>()->Value();
		int score = GetGSComponent<Score>()->Value();
		int game_speed = GetGSComponent<GameSpeed>()->Value();
		int max_speed = GetGSComponent<GameSpeed>()->GetMax();

		int player_hp = player_ptr->GetHP();

		ImGui::Text("Killed Monster : %d", score);
		ImGui::Text("Gold : %d", gold);
		ImGui::Text("Life : %d", life);
		ImGui::Text("Player HP : %d", player_hp);
		ImGui::Text("Game Speed : %d", game_speed);


		if (ImGui::SliderInt("Adjust Gold", &gold, 0, 100000, "%d")) {
			GetGSComponent<Gold>()->SetValue(gold);
		}
		if (ImGui::SliderInt("Adjust Life", &life, 1, 50, "%d")) {
			GetGSComponent<Life>()->SetValue(life);
		}
		if (ImGui::SliderInt("Player HP", &player_hp, 1, 20, "%d")) {
			player_ptr->SetHP(player_hp);
		}
		if (ImGui::SliderInt("Adjust Game Speed", &game_speed, 0, max_speed, "%d")) {
			GetGSComponent<GameSpeed>()->SetValue(game_speed);
		}

	}
	ImGui::End();


	ImGui::Begin("Produce");
	{
		if (ImGui::Button("Produce Basic Monster"))
		{
			Engine::GetLogger().LogEvent("Basic Monster Produce!");
			//MonsterFactory::CreateBasicMonsterFromFile();
			new Basic_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster());
		}
		if (ImGui::Button("Produce Fast Monster"))
		{
			Engine::GetLogger().LogEvent("Fast Monster Produce!");
			//MonsterFactory::CreateFastMonsterFromFile();
			new Fast_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Fast_Monster());
		}
		if (ImGui::Button("Produce Slow Monster"))
		{
			Engine::GetLogger().LogEvent("Slow Monster Produce!");
			//MonsterFactory::CreateSlowMonsterFromFile();
			new Slow_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Slow_Monster());
		}
		if (ImGui::Button("Produce Mother Monster"))
		{
			Engine::GetLogger().LogEvent("Mother Monster Produce!");
			//MonsterFactory::CreateSlowMonsterFromFile();
			new Mother_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Slow_Monster());
		}
		if (ImGui::Button("Produce Weak Monster"))
		{
			Engine::GetLogger().LogEvent("Weak Monster Produce!");
			//MonsterFactory::CreateSlowMonsterFromFile();
			new Weak_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Slow_Monster());
		}
		if (ImGui::Button("Produce Heal Monster"))
		{
			Engine::GetLogger().LogEvent("Heal Monster Produce!");
			//MonsterFactory::CreateSlowMonsterFromFile();
			new Heal_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Slow_Monster());
		}
		if (ImGui::Button("Produce Stealth Monster"))
		{
			Engine::GetLogger().LogEvent("Stealth Monster Produce!");
			//MonsterFactory::CreateSlowMonsterFromFile();
			new Stealth_Monster;
			//GetGSComponent<GAM200::GameObjectManager>()->Add(new Slow_Monster());
		}


		if (ImGui::Button("Produce Basic Tower"))
		{
			GetGSComponent<BuildMode>()->Build(GameObjectTypes::Basic_Tower);
		}
		if (ImGui::Button("Produce Double Tower"))
		{
			GetGSComponent<BuildMode>()->Build(GameObjectTypes::Double_Tower);
		}
		if (ImGui::Button("Produce Triple Tower"))
		{
			GetGSComponent<BuildMode>()->Build(GameObjectTypes::Triple_Tower);
		}
		if (ImGui::Button("Produce Push Tower"))
		{
			GetGSComponent<BuildMode>()->Build(GameObjectTypes::Push_Tower);
		}
		if (ImGui::Button("Produce Wide Tower"))
		{
			GetGSComponent<BuildMode>()->Build(GameObjectTypes::Wide_Tower);
		}


		if (ImGui::Button("Delete Tower"))
		{
			GetGSComponent<BuildMode>()->DeleteTower();
		}
		if (ImGui::Button("Change tile to Pass tile"))
		{
			GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Pass__Tile);
		}
		if (ImGui::Button("Change tile to Block tile"))
		{
			GetGSComponent<BuildMode>()->ChangeTile(GameObjectTypes::Obstacle);
		}

		if (ImGui::Button("Show Current Tower Info"))
		{
			Tower_Adopter::GetInstance().Show_Info();
		}
		if (ImGui::Button("Delete Current Tower"))
		{
			Tower_Adopter::GetInstance().Delete();
		}
		if (ImGui::Button("Upgrade Current Tower"))
		{
			Tower_Adopter::GetInstance().Upgrade();
		}
	}
	ImGui::End();


}

void GamePlayEditor::HandleEvent(SDL_Event& event)
{

}


void GamePlayEditor::SetMap(std::string file_name)
{
	// Set Map
	Map::GetInstance().SetMap(file_name);

	// Window, tiles
	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	tile_col = Map::GetInstance().GetSize().x;
	tile_row = Map::GetInstance().GetSize().y;
	tile_size.x = window_size.x / tile_row;
	tile_size.y = window_size.y / tile_col;

	Astar::GetInstance().UpdatePath(Map::GetInstance().GetMap(), Map::GetInstance().GetStartPoint(), Map::GetInstance().GetEndPoint());
}

