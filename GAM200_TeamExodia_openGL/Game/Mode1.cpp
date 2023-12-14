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


#include <filesystem>
#include <imgui.h>
#include <stb_image.h>
#include <glCheck.h>
#include "../Engine/Audio.h"

#include "../Engine/Engine.h"
#include "../Engine/DrawShape.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Collision.h"

#include "../Game/Mode1.h"
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
#include "Map.h"
#include "ModeSelect.h"
#include "Fonts.h"
#include "Monster.h"

Mode1::Mode1() : player_ptr()
{

}

void Mode1::Load()
{

	// Game Object
	AddGSComponent(new GAM200::GameObjectManager());

	// Camera
	AddGSComponent(new GAM200::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));

	// Set Map
	switch (ModeSelect::GetCount())
	{
	case 0:
		Mode1::SetMap("assets/maps/Map1.txt");
		break;
	case 1:
		Mode1::SetMap("assets/maps/Map2.txt");
		break;
	case 2:
		Mode1::SetMap("assets/maps/Map3.txt");
		break;
	}

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
	MonsterFactory::InitBombMonsterFromFile();

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

void Mode1::Update(double dt)
{


	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Tab))
	{
		GetGSComponent<GameSpeed>()->NextSpeed();
	}
	dt *= static_cast<double>(GetGSComponent<GameSpeed>()->Value());


	GetGSComponent<GAM200::Camera>()->Update(player_ptr->GetPosition());
	//GetGSComponent<GAM200::Camera>()->SetPosition(player_ptr->GetPosition());

	GetGSComponent<GAM200::GameObjectManager>()->UpdateAll(dt);

	GetGSComponent<GAM200::GameObjectManager>()->CollisionTest();

	GetGSComponent<Wave>()->Update(dt);

	GetGSComponent<BuildMode>()->Update();

	GetGSComponent<ShowPath>()->Update();

#ifdef _DEBUG
	GetGSComponent<GAM200::ShowCollision>()->Update(dt);
#endif

	Engine::GetWindow().Clear(1.0f, 1.0f, 1.0f, 1.0f);

	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::ModeSelect));
	}

	if (GetGSComponent<Life>()->Value() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Lose));
	}
	int gold = GetGSComponent<Gold>()->Value();
	int score = GetGSComponent<Score>()->Value();
	int player_hp = player_ptr->GetHP();
	int wall_hp = GetGSComponent<Score>()->Value();
	int life = GetGSComponent<Life>()->Value();
	int boost = player_ptr->GetDashCount();

	GetGSComponent<HBG_Ui>()->Player_BOOST = boost;
	GetGSComponent<HBG_Ui>()->Player_HP = player_hp;
	//GetGSComponent<HBG_Ui>()->Player_HP = main_hp;
	GetGSComponent<HBG_Ui>()->Tower_GOLD = gold;
	GetGSComponent<HBG_Ui>()->wall_hp = life;



	remaining_gold.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("G: " + std::to_string(gold), 0xffffff));

	wave_info.reset(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Wave: " + std::to_string(GetGSComponent<Wave>()->GetCurrentWave()) + "/" + std::to_string(GetGSComponent<Wave>()->GetMaxWave()), 0xffffff));

}

void Mode1::Unload()
{
	player_ptr = nullptr;
	Map::GetInstance().MapUnload();
	Monster::remaining_monsters = 0;
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

	Math::TransformationMatrix camera_matrix = GetGSComponent<GAM200::Camera>()->GetMatrix();

	//GetGSComponent<Background>()->Draw(*GetGSComponent<GAM200::Camera>());




	//timer_texture.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 5 }));
	//score.Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture.GetSize().x, Engine::GetWindow().GetSize().y - timer_texture.GetSize().y - 80 }));

	GetGSComponent<GAM200::GameObjectManager>()->DrawAll(camera_matrix);

	GetGSComponent<ShowPath>()->DrawPath();


	GetGSComponent<BuildMode>()->Draw();
	player_ptr->Draw(camera_matrix);


	remaining_gold->Draw(Math::TranslationMatrix(Math::ivec2{ 130, 720 - 95 }));
	wave_info->Draw(Math::TranslationMatrix(Math::ivec2{ 1000, 720 - 0 }));

	GetGSComponent<HBG_Ui>()->Draw();

}

void Mode1::ImguiDraw()
{

}

void Mode1::HandleEvent(SDL_Event& event)
{

}


void Mode1::SetMap(std::string file_name)
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

