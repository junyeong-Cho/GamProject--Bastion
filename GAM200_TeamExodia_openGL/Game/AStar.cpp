


#include "Astar.h"

//Astar::Astar( ) {
//
//}


void Astar::UpdatePath(int** map, Math::ivec2 start, Math::ivec2 target) {
	std::vector<Math::ivec2> openList;
	std::vector<Math::ivec2> closedList;

	// Clear vectors
	openList.clear();
	closedList.clear();
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
		double optimalCost = std::numeric_limits<double>::max();
		for (const Math::ivec2& neighbor : neighbors) {
			if (std::find_if(closedList.begin(), closedList.end(),
				[&](Math::ivec2& element) { return element == neighbor; }) != closedList.end()) {
				continue;
			}
			if (map[neighbor.y][neighbor.x] == 5)
				continue;

			path[neighbor] = current;
			openList.push_back(neighbor);

			int actualCost = static_cast<int>(path.size());
			int ManhattanDistanceCost = (abs(target.x - neighbor.x) + abs(target.y - neighbor.y));
			int neighborCost = actualCost + ManhattanDistanceCost;

			if (neighborCost < optimalCost) {
				optimalCost = neighborCost;
				optimalNeighbor = neighbor;
			}
		}
		Math::ivec2 nextPosition = current;
		while (path.count(current) > 0) {
			nextPosition = current;
			current = path[current];
			if (current == start)
				break;
		}
	}

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