#pragma once

#include "../Engine/GameState.h"
#include "GameObjectTypes.h"
#include "../Engine/Vec2.h"
#include "../Engine/Audio.h"

#include <tuple>

class Tile;
class Tower;

struct Info
{
public:
	Tile* tile;
	Tower* tower;

	Info() : tile(nullptr), tower(nullptr) { }
};

class Map {
public:
	static Map& GetInstance() {
		static Map instance;
		return instance;
	}

	Info*** GetMap() {
		return map;
	}
	void SetMap(std::string file_name);
	Math::ivec2 GetStartPoint() const { return start_point; }
	Math::ivec2 GetEndPoint() const { return end_point; }
	void MapUnload() const;
	Math::ivec2 GetSize() const { return Math::ivec2(cols, rows); }
	std::vector<std::vector<std::tuple<int, std::string, int>>> GetWaveInfo() const { return wave_info; }
	std::string GetType(Math::ivec2 position) const;
	Tower* GetTower(Math::ivec2 position) const;

	void ChangeTile(Math::ivec2 position, GameObjectTypes type);

	void DeleteTower(Math::ivec2 position);
	void BuildTower(Math::ivec2 position, GameObjectTypes type, int direction);

	bool editor_mode = false;

private:


	Info*** map = nullptr;

	Math::ivec2 start_point;
	Math::ivec2 end_point;

	int cols = 0;
	int rows = 0;

	Math::ivec2 tile_size;

	int wave_num = 0;
	std::vector<std::vector<std::tuple<int, std::string, int>>> wave_info;
};