#pragma once

#include "../Engine/GameState.h"
#include "Game/GameObjectTypes.h"
#include "Engine/Vec2.h"

class Map {
public:
	static Map& GetInstance() {
		static Map instance;
		return instance;
	}

	int** GetMap() {
		return map;
	}
	void SetMap(std::string file_name);
	Math::ivec2 GetStartPoint() const { return start_point; }
	Math::ivec2 GetEndPoint() const { return end_point; }
	void MapUnload();

private:
	int** map = nullptr;

	Math::ivec2 start_point;
	Math::ivec2 end_point;

	int cols = 0;
	int rows = 0;

};




/*
9
16

0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 1 1 1 0 0 0 0 0
0 0 0 0 0 1 0 0 1 0 0 0 0 0
0 0 1 1 1 1 0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0 1 1 1 1 1 1
0 0 1 0 0 0 0 0 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0 0 0 0 0 0




*/