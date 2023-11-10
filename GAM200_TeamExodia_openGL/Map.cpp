
#include <iostream>
#include <fstream>

#include "Map.h"
#include "Engine/Engine.h"

void Map::SetMap(std::string file_name) {
	std::ifstream file(file_name);

	// File parsing and get cols and rows
	if (file.is_open()) {
		// cols, rows
		file >> cols;
		file >> rows;

		// Then dynamic allocate
		map = new int* [cols];
		for (int i = 0; i < cols; ++i) {
			map[i] = new int[rows];
		}

		// Get and set informations
		for (int y = 0; y < cols; ++y)
		{
			for (int x = 0; x < rows; ++x)
			{
				char tileType;

				file >> tileType;

				if (tileType == 'P')
				{
					map[y][x] = static_cast<int>(GameObjectTypes::Pass__Tile);
				}
				else if (tileType == 'B')
				{
					map[y][x] = static_cast<int>(GameObjectTypes::Block_Tile);
				}

			}
		}

		// Set start and end point
		file >> start_point.x;
		file >> start_point.y;
		file >> end_point.x;
		file >> end_point.y;

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