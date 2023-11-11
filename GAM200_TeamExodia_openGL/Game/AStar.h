#pragma once

#include "../Engine/Vec2.h"
#include <unordered_map>
#include <vector>

class Tile;
class Astar {
public:
	static Astar& GetInstance() {
		static Astar instance;
		return instance;
	}
	std::vector<Math::ivec2>& GetPath() { return path; }
	void UpdatePath(Tile*** map, Math::ivec2 start, Math::ivec2 target);
private:
	Astar() = default;

	std::vector<Math::ivec2> path;
	std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position);
};