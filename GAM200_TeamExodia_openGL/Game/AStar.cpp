


#include "Astar.h"
#include <limits>
#include "../Engine/Engine.h"
#include "GameObjectTypes.h"
#include "../Map.h"
#include "Tile.h"

void Astar::UpdatePath(Tile*** map, Math::ivec2 start, Math::ivec2 target) {
	std::vector<Math::ivec2> openList;
	std::vector<Math::ivec2> closedList;
	std::unordered_map<Math::ivec2, Math::ivec2> cameFrom;

	openList.clear();
	closedList.clear();
	cameFrom.clear();

	path.clear();

	openList.push_back(start);

	Math::ivec2 current;
	while (!openList.empty()) {
		current = openList.front();
		openList.erase(openList.begin());

		if (current == target)
			break;

		std::vector<Math::ivec2> neighbors = GetNeighboringTiles(current);
		Math::ivec2 optimalNeighbor = current;
		int optimalCost = std::numeric_limits<int>::max();

		for (const Math::ivec2& neighbor : neighbors) {
			if (std::find_if(closedList.begin(), closedList.end(),
				[&](const Math::ivec2& element) { return element == neighbor; }) != closedList.end()) {
				continue;
			}
			if (map[neighbor.y][neighbor.x]->Type() == (GameObjectTypes::Block_Tile))
				continue;

			cameFrom[neighbor] = current;
			openList.push_back(neighbor);

			int actualCost = static_cast<int>(cameFrom.size());
			int ManhattanDistanceCost = (abs(target.x - neighbor.x) + abs(target.y - neighbor.y));
			int neighborCost = actualCost + ManhattanDistanceCost;

			if (neighborCost < optimalCost) {
				optimalCost = neighborCost;
				optimalNeighbor = neighbor;
			}
		}
		closedList.push_back(current);

		if (optimalNeighbor != current) {
			current = optimalNeighbor;
		}
	}

	Math::ivec2 last_direction = current - cameFrom[current];

	path.insert(path.begin(), current + last_direction);
	path.insert(path.begin(), current + last_direction);
	path.insert(path.begin(), current);

	Math::ivec2 direction;

	while (cameFrom.count(current) > 0) {
		//Engine::GetLogger().LogDebug(std::to_string(current.x) + ", " + std::to_string(current.y) + "\n");

		current = cameFrom[current];
		path.insert(path.begin(), current);

		if (current == start)
			break;

		direction = current - cameFrom[current];
	}

	Math::ivec2 start_direction = direction;
	
	path.insert(path.begin(), start - start_direction);

}


std::vector<Math::ivec2> Astar::GetNeighboringTiles(const Math::ivec2& position) {
	std::vector<Math::ivec2> neighbors;

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