
#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/GameObject.h"

#include "AStar.h"
#include "Tile.h"
#include "Tower.h"
#include "Gold.h"

void Map::SetMap(std::string file_name)
{



	std::ifstream file(file_name);

	// File parsing and get cols and rows
	if (file.is_open()) {
		// 1 -> editor, 0 -> game
		file >> editor_mode;
		// cols, rows
		file >> cols;
		file >> rows;

		// Then dynamic allocate
		map = new Info * *[cols];
		for (int i = 0; i < cols; ++i) {
			map[i] = new Info * [rows];
			for (int j = 0; j < rows; ++j)
			{
				map[i][j] = new Info();
			}
		}

		// Set Tile size
		Math::ivec2 window_size = Engine::GetWindow().GetSize();
		tile_size.x = window_size.x / rows;
		tile_size.y = window_size.y / cols;

		// Get and set informations
		for (int y = 0; y < cols; ++y)
		{
			for (int x = 0; x < rows; ++x)
			{
				char tileType;

				file >> tileType;

				if (tileType == 'P')
				{
					map[y][x]->tile = new Pass__Tile(Math::irect{ { x * tile_size.x, y * tile_size.y }, { (x + 1) * tile_size.x, (y + 1) * tile_size.y } });
				}
				else if (tileType == 'B')
				{
					map[y][x]->tile = new Block_Tile(Math::irect{ { x * tile_size.x, y * tile_size.y }, { (x + 1) * tile_size.x, (y + 1) * tile_size.y } });
				}
				else if (tileType == 'C')
				{
					map[y][x]->tile = new Cliff(Math::irect{ { x * tile_size.x, y * tile_size.y }, { (x + 1) * tile_size.x, (y + 1) * tile_size.y } });
				}
			}
		}

		// Set start and end point
		file >> start_point.x; file >> start_point.y;
		file >> end_point.x;   file >> end_point.y;

		// Wave info!
		file >> wave_num;

		wave_info.clear();
		wave_info.resize(wave_num);

		std::string info;
		for (int i = 0; i < wave_num; ++i)
		{
			wave_info[i].clear();
			while (1)
			{
				file >> info;
				if (info == "END")
					break;
				else if (info == "WAVE")
				{
					int time;
					std::string type;
					int number;

					file >> time;
					file >> type;
					file >> number;

					wave_info[i].emplace_back(std::make_tuple(time, type, number));
				}
				else
				{
					std::cerr << "Wrong input!" << std::endl;
				}

			}
		}
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}


}

void Map::MapUnload() const {
	// Free the Memoroy
	for (int i = 0; i < cols; ++i) {
		delete[] map[i];
	}
	delete[] map;
}

void Map::ChangeTile(Math::ivec2 position, GameObjectTypes type) {
	int cols = position.y;
	int rows = position.x;

	if (map[cols][rows]->tile->Type() == type || map[cols][rows]->tile->Type() == GameObjectTypes::Block_Tile)
	{
		GAM200::SoundEffect::cannot_select().Big_play();

		Engine::GetLogger().LogDebug("It's same type of tile or it's block tile!");
		return;
	}

	if ((position.x == start_point.y && position.y == start_point.x) || (position.x == end_point.y && position.y == end_point.x))
	{
		GAM200::SoundEffect::cannot_select().Big_play();

		Engine::GetLogger().LogDebug("You cannot change the start point or end point!");
		return;
	}

	if (type == GameObjectTypes::Pass__Tile)
	{
		map[cols][rows]->tile->Tile_Destroy();
		map[cols][rows]->tile = nullptr;
		delete map[cols][rows]->tile;

		map[cols][rows]->tile = new Pass__Tile(Math::irect{ { rows * tile_size.x, cols * tile_size.y }, { (rows + 1) * tile_size.x, (cols + 1) * tile_size.y } });

		Engine::GetLogger().LogDebug("Changed to pass tile!");
	}
	else if (type == GameObjectTypes::Block_Tile)
	{
		/*map[cols][rows]->tile->Tile_Destroy();
		map[cols][rows]->tile = nullptr;
		delete map[cols][rows]->tile;

		map[cols][rows]->tile = new Block_Tile(Math::irect{ { rows * tile_size.x, cols * tile_size.y }, { (rows + 1) * tile_size.x, (cols + 1) * tile_size.y } });*/
		return;
	}
	else if (type == GameObjectTypes::Obstacle)
	{
		map[cols][rows]->tile->Tile_Destroy();
		map[cols][rows]->tile = nullptr;
		delete map[cols][rows]->tile;

		map[cols][rows]->tile = new Obstacle(Math::irect{ { rows * tile_size.x, cols * tile_size.y }, { (rows + 1) * tile_size.x, (cols + 1) * tile_size.y } });

		Engine::GetLogger().LogDebug("Changed to obstacle tile!");
	}

	if (Astar::GetInstance().UpdatePath(map, start_point, end_point) == false)
	{
		GAM200::SoundEffect::cannot_select().Big_play();

		Engine::GetLogger().LogDebug("You cannot change this tile!");
		ChangeTile(position, GameObjectTypes::Pass__Tile);
		Astar::GetInstance().UpdatePath(map, start_point, end_point);
	}
}


void Map::DeleteTower(Math::ivec2 position)
{
	int cols = position.y;
	int rows = position.x;

	if (map[cols][rows]->tower == nullptr)
	{

		Engine::GetLogger().LogDebug("There is no tower!");
		return;
	}

	map[cols][rows]->tower->Tower_Destroy();
	map[cols][rows]->tower = nullptr;
}

void Map::BuildTower(Math::ivec2 position, GameObjectTypes type, int direction)
{
	int cols = position.y;
	int rows = position.x;

	if (map[cols][rows]->tower != nullptr)
	{
		GAM200::SoundEffect::cannot_select().Big_play();

		Engine::GetLogger().LogDebug("There is a tower already!");
		return;
	}

	if (map[cols][rows]->tile->Type() != GameObjectTypes::Block_Tile)
	{
		GAM200::SoundEffect::cannot_select().Big_play();

		Engine::GetLogger().LogDebug("Not able here! It's " + map[cols][rows]->tile->TypeName());
		return;
	}

	switch (type)
	{
	case GameObjectTypes::Basic_Tower:
		if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Basic_Tower::GetCost())
		{
			GAM200::SoundEffect::cannot_select().Big_play();

			Engine::GetLogger().LogDebug("Not enough gold!");
			return;
		}
		//map[cols][rows]->tower = TowerFactory::CreateBasicTowerFromFile({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		map[cols][rows]->tower = new Basic_Tower({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		break;
	case GameObjectTypes::Double_Tower:
		if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Double_Tower::GetCost())
		{
			GAM200::SoundEffect::cannot_select().Big_play();

			Engine::GetLogger().LogDebug("Not enough gold!");
			return;
		}
		//map[cols][rows]->tower = TowerFactory::CreateDoubleTowerFromFile({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		map[cols][rows]->tower = new Double_Tower({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		break;
	case GameObjectTypes::Triple_Tower:
		if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Triple_Tower::GetCost())
		{
			GAM200::SoundEffect::cannot_select().Big_play();

			Engine::GetLogger().LogDebug("Not enough gold!");
			return;
		}
		//map[cols][rows]->tower = TowerFactory::CreateTripleTowerFromFile({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		map[cols][rows]->tower = new Triple_Tower({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		break;
	case GameObjectTypes::Push_Tower:
		if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Push_Tower::GetCost())
		{
			GAM200::SoundEffect::cannot_select().Big_play();

			Engine::GetLogger().LogDebug("Not enough gold!");
			return;
		}
		//map[cols][rows]->tower = TowerFactory::CreateBasicTowerFromFile({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		map[cols][rows]->tower = new Push_Tower({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		break;
	case GameObjectTypes::Wide_Tower:
		if (Engine::GetGameStateManager().GetGSComponent<Gold>()->Value() < Wide_Tower::GetCost())
		{
			GAM200::SoundEffect::cannot_select().Big_play();

			Engine::GetLogger().LogDebug("Not enough gold!");
			return;
		}
		//map[cols][rows]->tower = TowerFactory::CreateBasicTowerFromFile({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		map[cols][rows]->tower = new Wide_Tower({ static_cast<double>(rows * static_cast<double>(tile_size.x)), (cols * static_cast<double>(tile_size.y)) }, static_cast<int>(direction));
		break;
	}
	Engine::GetLogger().LogDebug("Tower build!");
}


std::string Map::GetType(Math::ivec2 position) const
{
	return map[position.y][position.x]->tile->TypeName();
}

Tower* Map::GetTower(Math::ivec2 position) const
{
	int cols = position.y;
	int rows = position.x;

	return map[cols][rows]->tower;
}