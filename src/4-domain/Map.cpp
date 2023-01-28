#include "Map.h"

//X first
std::pair<int, int> Map::toCoordinate(const int &i) const {
    const int y = i / width;
    const int x = i % width;
    return {x, y};
}

Map::~Map() {
    delete[] array;
}

void Map::set(const unsigned &i, const int &value) {
    array[i] = value;

    if (value < min) {
        min = value;
    }
    if (value > max) {
        max = value;
    }
}
