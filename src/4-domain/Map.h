#pragma once

#include <functional>
#include <cstdint>
#include "Coord.h"
#include "ColorInterpolate.h"

class Map {
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
		array(other.array) {
	}

	Map& operator=(const Map& other) = delete;

	Map& operator=(Map&& other) = delete;


	Map(unsigned int w, unsigned int h)
		: width(w),
		height(h),
		size(h* w) {
		array = new int[w * h]();
	}

	[[nodiscard]] std::pair<int, int> toCoordinate(const int& i) const;

	~Map();

	void set(const unsigned& i, const int& value);

	void set(const Coord& i, const int& value);

	[[nodiscard]] int get(const Coord& i) const;

	void prepareRender();

	[[nodiscard]] unsigned render(const unsigned& i) const;

	int* array;

	void setColorRender(std::vector<unsigned>&& colors);

private:
	std::vector<unsigned> colors{
		0xFF000000,
			0xFF0000FF,
			0xFF00FFFF,
			0xFF00FF00,
			0xFFFFFF00,
			0xFFFF0000,
			0xFFFFFFFF,
	};
	ColorInterpolate<int> colorInterpolate{ 0,5 };
};

