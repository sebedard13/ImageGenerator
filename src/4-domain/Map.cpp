#include "Map.h"


//X first
std::pair<int, int> Map::toCoordinate(const int& i) const {
	const int y = i / width;
	const int x = i % width;
	return { x, y };
}

Map::~Map() {
	delete[] array;
}

void Map::set(const unsigned& i, const int& value) {
	array[i] = value;

	if (value < min) {
		min = value;
	}
	if (value > max) {
		max = value;
	}
}

void Map::set(const Coord& c, const int& value) {
	set(c.getY() * width + c.getX(), value);
}

int Map::get(const Coord& c) const {
	return array[c.getY() * width + c.getX()];
}

void Map::prepareRender()
{
	colorInterpolate = ColorInterpolate<int>{ min, max, colors };
}

unsigned Map::render(const unsigned& i) const
{
	return colorInterpolate.uniformColor(array[i]);
}

void Map::setColorRender(std::vector<unsigned>&& colors)
{
	this->colors = std::move(colors);
}
