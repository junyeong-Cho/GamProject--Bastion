
#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/GameObject.h"

#include "AStar.h"
#include "Tile.h"

void Map::SetMap(std::string file_name) {
	std::ifstream file(file_name);

	// File parsing and get cols and rows
	if (file.is_open()) {
		// cols, rows
		file >> cols;
		file >> rows;

		// Then dynamic allocate
		map = new Tile** [cols];
		for (int i = 0; i < cols; ++i) {
			map[i] = new Tile*[rows];
			for (int j = 0; j < rows; ++j)
				map[i][j] = nullptr;
		}

		// Set Tile size
		Math::ivec2 window_size = Engine::GetWindow().GetSize();
		tile_size_x = window_size.x / rows;
		tile_size_y = window_size.y / cols;

		// Get and set informations
		for (int y = 0; y < cols; ++y)
		{
			for (int x = 0; x < rows; ++x)
			{
				char tileType;

				file >> tileType;

				if (tileType == 'P')
				{
					map[y][x] = new Pass__Tile(Math::irect{ { x * tile_size_x, y * tile_size_y }, { (x + 1) * tile_size_x, (y + 1) * tile_size_y } });
					//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Pass__Tile(Math::irect{ { x * tile_size_x, y * tile_size_y }, { (x + 1) * tile_size_x, (y + 1) * tile_size_y } }));
					//*map[y][x] = static_cast<int>(GameObjectTypes::Pass__Tile);
				}
				else if (tileType == 'B')
				{
					map[y][x] = new Block_Tile(Math::irect{ { x * tile_size_x, y * tile_size_y }, { (x + 1) * tile_size_x, (y + 1) * tile_size_y } });
					//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Block_Tile(Math::irect{ { x * tile_size_x, y * tile_size_y }, { (x + 1) * tile_size_x, (y + 1) * tile_size_y } }));
					//map[y][x] = static_cast<int>(GameObjectTypes::Block_Tile);
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

void Map::MapUnload() {
	// Free the Memoroy
	for (int i = 0; i < cols; ++i) {
		delete[] map[i];
	}
	delete[] map;
}

void Map::ChangeTile(Math::ivec2 position, GameObjectTypes type) {
	int cols = position.x;
	int rows = position.y;

	delete map[cols][rows];
	if (type == GameObjectTypes::Pass__Tile) 
	{
		Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Pass__Tile(Math::irect{ { rows * tile_size_x, cols * tile_size_y }, { (rows + 1) * tile_size_x, (cols + 1) * tile_size_y } }));
	}
	else if (type == GameObjectTypes::Block_Tile)
	{
		Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Block_Tile(Math::irect{ { rows * tile_size_x, cols * tile_size_y }, { (rows + 1) * tile_size_x, (cols + 1) * tile_size_y } }));
	}

	Astar::GetInstance().UpdatePath(map, start_point, end_point);
}

std::string Map::GetType(Math::ivec2 position) const
{
	return map[position.y][position.x]->TypeName();
}