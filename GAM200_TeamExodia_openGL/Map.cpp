#include "Map.h"



void Map::SetMap(std::string file_name) {

}

void Map::SetMap1() {
	// File parsing and get cols and rows
	cols = 9;
	rows = 16;
	// Then dynamic allocate
	map = new int* [cols];
	for (int i = 0; i < cols; ++i) {
		map[i] = new int[rows];
	}
	// Get and set informations
	int map_info[9][16] = {
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile)
	};

	int index = 0;
	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < rows; ++j)
			map[i][j] = map_info[i][j];
	}
	// Set start and end point
	start_point = Math::ivec2(0, 0);
	end_point = Math::ivec2(8, 13);
}


void Map::SetMap2() {
	// File parsing and get cols and rows
	cols = 9;
	rows = 16;
	// Then dynamic allocate
	map = new int* [cols];
	for (int i = 0; i < cols; ++i) {
		map[i] = new int[rows];
	}
	// Get and set informations
	int map_info[9][16] = {
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile),
	static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Block_Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile), static_cast<int>(GameObjectTypes::Pass__Tile)
	};
	
	int index = 0;
	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < rows; ++j)
			map[i][j] = map_info[i][j];
	}
	// Set start and end point
	start_point = Math::ivec2(0, 0);
	end_point = Math::ivec2(8, 15);
}


void Map::MapUnload() {
	// Free the Memoroy
	for (int i = 0; i < cols; ++i) {
		delete[] map[i];
	}
	delete[] map;
}