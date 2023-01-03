#include "Map.h"

#include <iostream>

void Map::forAll(std::function<int(int, int, int)> func)
{
	int arrayl = width * height;

	std::cout << "For all " << 0 << "/" << arrayl<<"\r";

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
		std::cout << "For all " << y*width << "/" << arrayl << "\r";
	}
	std::cout << "For all " << height * width << "/" << arrayl << std::endl;
}

void Map::forEach(std::function<void(int, int, int)> func) const
{
	int arrayl = width * height;

	std::cout << "For each " << 0 << "/" << arrayl << "\r";

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{

			auto i = x + y * width;
			func(x, y, array[i]);
		}
		std::cout << "For each " << y * width << "/" << arrayl << "\r";
	}
	std::cout << "For each " << height * width << "/" << arrayl << std::endl;
}

Map::~Map()
{
	delete[] array;
}
