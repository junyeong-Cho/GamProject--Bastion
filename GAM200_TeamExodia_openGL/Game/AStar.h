#pragma once

#include "../Engine/Vec2.h"
#include <unordered_map>
#include <vector>

class Tile;
struct Info;

class Astar {
public:
	// Singleton pattern
	static Astar& GetInstance() 
	{
		static Astar instance;
		return instance;
	}

	// Getter function for the path
	std::vector<Math::ivec2>& GetPath() { return path; }

	// Function to update the pathfinding based on A* algorithm
	bool UpdatePath(Info*** map, Math::ivec2 start, Math::ivec2 target);

private:
	// Constructor set as private to implement the Singleton pattern
	Astar() = default;

	// Variable for check if the pathfinding is successful
	bool is_okay = false;

	// Vector to store the final path
	std::vector<Math::ivec2> path;

	// Function to get neighboring tiles of a given position
	std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position);
};