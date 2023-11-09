#pragma once

#include "../Engine/GameState.h"
#include "Game/GameObjectTypes.h"


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
	void SetMap1();

private:
	int** map;



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