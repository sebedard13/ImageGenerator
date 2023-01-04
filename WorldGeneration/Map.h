#pragma once
#include <functional>

class Map
{
public:
	const unsigned int width;
	const unsigned int height;
	const unsigned int size;
	int min = INT32_MAX;
	int max = INT32_MIN;

	Map(const Map& other) = delete;

	Map(Map&& other) noexcept
		: width(other.width),
		height(other.height),
		size(other.size),
		array(other.array)
	{
	}

	Map& operator=(const Map& other) = delete;

	Map& operator=(Map&& other) = delete;

	Map(unsigned int w, unsigned int h) :width(w), height(h), size(h* w)
	{
		array = new int[w * h];
	}

	void forAll(std::function<int(const unsigned int& v, const unsigned int& x, const unsigned int& y, const unsigned int& i)> func);

	void forEach(std::function<int(const unsigned int& v, const unsigned int& x, const unsigned int& y, const unsigned int& i)> func) const;

	~Map();

	int* array;
private:
};

