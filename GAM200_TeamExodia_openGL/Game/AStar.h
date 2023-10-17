#pragma once

#include "../Engine/Vec2.h"
#include <unordered_map>
#include <vector>

class Astar {
public:
	static Astar& GetInstance() {
		static Astar instance;
		return instance;
	}
	std::unordered_map<Math::ivec2, Math::ivec2>& GetPath() { return path; }
	void UpdatePath(int map[9][16], Math::ivec2 start, Math::ivec2 target);
private:
	Astar() = default;
	//Astar( );
	//std::unordered_map<Math::ivec2, Math::ivec2> path;
	std::vector<Math::ivec2> path;
	std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position);
};