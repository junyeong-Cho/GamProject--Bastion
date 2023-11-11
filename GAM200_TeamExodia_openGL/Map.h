#pragma once

#include "../Engine/GameState.h"
#include "Game/GameObjectTypes.h"
#include "Engine/Vec2.h"

class Tile;
class Map {
public:
	static Map& GetInstance() {
		static Map instance;
		return instance;
	}

	Tile*** GetMap() {
		return map;
	}
	void SetMap(std::string file_name);
	Math::ivec2 GetStartPoint() const { return start_point; }
	Math::ivec2 GetEndPoint() const { return end_point; }
	void MapUnload();
	Math::ivec2 GetSize() const { return Math::ivec2(cols, rows); }

	void ChangeTile(Math::ivec2 position, GameObjectTypes type);

private:
	Tile*** map = nullptr;

	Math::ivec2 start_point;
	Math::ivec2 end_point;

	int cols = 0;
	int rows = 0;

	int tile_size_x = 0;
	int tile_size_y = 0;

};