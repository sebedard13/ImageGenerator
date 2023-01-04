#include "Map.h"

void Map::forAll(std::function<int(const unsigned int& v, const unsigned int& x, const unsigned int& y, const unsigned int& i)> func)
{
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			const auto i = x + y * width;
			const int result = func(array[i], x, y, i);
			array[i] = result;

			if (result < min)
			{
				min = result;
			}
			if (result > max)
			{
				max = result;
			}
		}
	}
}

void Map::forEach(std::function<int(const unsigned int& v, const unsigned int& x, const unsigned int& y, const unsigned int& i)> func) const
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			auto i = x + y * width;
			func(array[i], x, y, i);
		}
	}
}

Map::~Map()
{
	delete[] array;
}
