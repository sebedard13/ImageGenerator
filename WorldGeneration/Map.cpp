#include "Map.h"

#include <iostream>

void Map::forAll(std::function<int(int, int, int)> func)
{
	int arrayl = width * height;

	
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
		
			auto i = x+y*width;
			int result = func(x,y, array[i]);
			array[i] = result;

			if(result < min)
			{
				min = result;
			}
			if(result>max)
			{
				max = result;
			}
		}
	}
}

void Map::forEach(std::function<void(int, int, int)> func) const
{
	int arrayl = width * height;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			auto i = x + y * width;
			func(x, y, array[i]);
		}
	}
}

Map::~Map()
{
	delete[] array;
}
