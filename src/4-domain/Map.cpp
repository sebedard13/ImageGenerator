#include "Map.h"

//X first
std::pair<int, int> Map::toCoordinate(const int& i) const {
	const int y = i / getWidth();
	const int x = i % getWidth();
	return { x, y };
}