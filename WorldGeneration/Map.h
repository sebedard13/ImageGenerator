#pragma once
#include <functional>

class Map
{
public:
	const int width;
	const int height;
	const int size;
	int min = INT32_MAX;
	int max = INT32_MIN;

	Map(const Map& other) = delete;

	Map(Map&& other) noexcept
		: width(other.width),
		  height(other.height),
		  array(other.array),size(other.size)
	{
	}

	Map& operator=(const Map& other) = delete;

	Map& operator=(Map&& other) = delete;

	Map(int w, int h) :width(w), height(h), size(h* w)
	{
		array = new int[w * h];
	}

	void forAll(std::function<int(int, int, int)> func);

	void forEach(std::function<void(int, int, int)> func) const;

	~Map();

	int* array;
private:
};

