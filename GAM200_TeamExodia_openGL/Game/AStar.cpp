


#include "Astar.h"
#include <limits>
#include "../Engine/Engine.h"
#include "GameObjectTypes.h"
#include "Map.h"
#include "Tile.h"


bool Astar::UpdatePath(Info*** map, Math::ivec2 start, Math::ivec2 target) {
	// Initialize openList, closedList, and a map, cameFrom, to store the path
	std::vector<Math::ivec2> openList;		// Tile that will be checked
	std::vector<Math::ivec2> closedList;	// Tile that has already checked
	std::unordered_map<Math::ivec2, Math::ivec2> cameFrom;	// Path Info

	// Clear existing path
	path.clear();

	// Put start position to openList
	openList.push_back(start);

	// Set is_okay to false
	// is_okay is true if AStar algorithm success to reach to the target position
	is_okay = false;

	Math::ivec2 current;

	// AStar algorithm loop
	while (!openList.empty()) {
		// Get the current position from the openList and erase it from the openList
		current = openList.front();
		openList.erase(openList.begin());

		// If current position is equal to target position, set is_okay to true and break
		if (current.x == target.y && current.y == target.x)
		{
			is_okay = true;
			break;
		}

		// Get neighboring tiles of the current position
		std::vector<Math::ivec2> neighbors = GetNeighboringTiles(current);

		
		Math::ivec2 optimalNeighbor = current;
		int optimalCost = std::numeric_limits<int>::max();

		// Iterate through neighbors to find the optimal path
		for (const Math::ivec2& neighbor : neighbors) {
			if (std::find_if(closedList.begin(), closedList.end(),
				[&](const Math::ivec2& element) { return element == neighbor; }) != closedList.end()) { // If the checking tile is in the closedList(already checked), continue
				continue;
			}
			if (map[neighbor.y][neighbor.x]->tile->Type() == (GameObjectTypes::Block_Tile) || // If the checking tile is Block_Tile or Obastacle(only check the Pass_Tile), continue
				map[neighbor.y][neighbor.x]->tile->Type() == (GameObjectTypes::Obstacle))
				continue;

			// Update path information
			cameFrom[neighbor] = current;
			openList.push_back(neighbor);

			// Calculate the cost using Manhattan distance method
			int actualCost = static_cast<int>(cameFrom.size());
			int ManhattanDistanceCost = (abs(target.x - neighbor.x) + abs(target.y - neighbor.y));
			int neighborCost = actualCost + ManhattanDistanceCost;

			// Check if the current neighbor provides a more optimal path
			if (neighborCost < optimalCost) {
				optimalCost = neighborCost;
				optimalNeighbor = neighbor;
			}
		}
		// Add the current position to the closed list
		closedList.push_back(current);

		// Update the current position if a more optimal neighbor is found
		if (optimalNeighbor != current) {
			current = optimalNeighbor;
		}
	}

	// Reconstruct the path if the target is reachable
	if (is_okay)
	{
		// Add the final positions to the path
		Math::ivec2 last_direction = current - cameFrom[current];

		// Uncomment the line below if needed
		//path.insert(path.begin(), current + last_direction);	// Set the end point to outside of the in-game map
		//path.insert(path.begin(), current + last_direction);	// Set the end point to outside of the in-game map
		path.insert(path.begin(), current);
		path.insert(path.begin(), current);

		Math::ivec2 direction;

		// Reconstruct the path based on the cameFrom map
		while (cameFrom.count(current) > 0) {
			current = cameFrom[current];
			path.insert(path.begin(), current);

			// Break the loop if the start position is reached
			if (current == start)
				break;

			direction = current - cameFrom[current];
		}

		Math::ivec2 start_direction = direction;

		// Uncomment the line below if needed
		// path.insert(path.begin(), start - start_direction);	// Set the starting point to outside of the in-game map
	}

	// Return is_okay to check the path is okay
	return is_okay;
}


std::vector<Math::ivec2> Astar::GetNeighboringTiles(const Math::ivec2& position) {
	std::vector<Math::ivec2> neighbors;

	// Check for valid neighboring positions and add them to the list
	if (position.x > 0) {
		neighbors.push_back({ position.x - 1, position.y });
	}
	if (position.x < 15) {
		neighbors.push_back({ position.x + 1, position.y });
	}
	if (position.y > 0) {
		neighbors.push_back({ position.x, position.y - 1 });
	}
	if (position.y < 8) {
		neighbors.push_back({ position.x, position.y + 1 });
	}

	return neighbors;
}