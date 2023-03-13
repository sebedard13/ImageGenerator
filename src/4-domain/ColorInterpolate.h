#pragma once

#include <qcolor.h>
#include <stdexcept>


//For unsigned
template<typename T>
class ColorInterpolate {

public:
	ColorInterpolate(const T& min, const T& max, std::vector<unsigned>& colors = defaultColors)
		: min(min),
		range(max - min) {
		this->colors = colors;
		step = static_cast<double> (range) / (this->colors.size() - 1);
	}

	ColorInterpolate(const ColorInterpolate<T>& other) = delete;

	ColorInterpolate(ColorInterpolate<T>&& other) noexcept
		: min(other.min),
		range(other.range),
		step(other.step)
	{
        colors = other.colors;
	}

	ColorInterpolate<T>& operator=(const ColorInterpolate<T>& other) = delete;

	ColorInterpolate<T>& operator=(ColorInterpolate<T>&& other) noexcept
	{
		if (this == &other)
			return *this;
		min = other.min;
		range = other.range;
		step = other.step;
        colors = other.colors;
		return *this;
	}

	unsigned uniformColor(const T& value) const {
		//Include max
		if (value == min + range) {
			return colors[colors.size() - 1];
		}

		const double v = (value - min);

		const int bin = v / step;

		const double normalized_v = (v - bin * step) / step;

		return interpolate(colors[bin], colors[bin + 1], normalized_v);
	}


private:

	static unsigned interpolate(const unsigned& cMin, const unsigned& cMax, const double& ratio) {
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		uint8_t red = ((1.0 - ratio) * qRed(cMin) + ratio * qRed(cMax));
		uint8_t green = ((1.0 - ratio) * qGreen(cMin) + ratio * qGreen(cMax));
		uint8_t blue = ((1.0 - ratio) * qBlue(cMin) + ratio * qBlue(cMax));

		unsigned color = 0x000000FF; //alpha
		color <<= 8;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;

		return color;
	}

	inline static std::vector<unsigned> defaultColors{
			0xFFe5f5f9,
			0xFF99d8c9,
			0xFF2ca25f,
	};

	double min, range, step;
	std::vector<unsigned> colors{};


};



template<>
class ColorInterpolate<int> {

public:
	ColorInterpolate(const int& min, const int& max, std::vector<unsigned>& colors = defaultColors)
		: min(min),
		range(max - min) {

		if (range > INT32_MAX / 4) {
			throw new std::invalid_argument("Range trop grand");
		}
		colorTable = new unsigned[range + 1];


		double step = static_cast<double> (range) / (colors.size() - 1);
		for (auto i = 0; i < range + 1; i++) {
			colorTable[i] = uniformColorCalcul(i + min, step, colors);
		}
	}

	ColorInterpolate(const ColorInterpolate<int>& other) = delete;

	ColorInterpolate(ColorInterpolate<int>&& other) noexcept
		: min(other.min),
		range(other.range),
		colorTable(other.colorTable)
	{
		other.colorTable = nullptr;
	}

	ColorInterpolate<int>& operator=(const ColorInterpolate<int>& other) = delete;

	ColorInterpolate<int>& operator=(ColorInterpolate<int>&& other) noexcept
	{
		if (this == &other)
			return *this;
		min = other.min;
		range = other.range;
		colorTable = other.colorTable;
		other.colorTable = nullptr;
		return *this;
	}


	unsigned uniformColor(const int& value) const {
		return colorTable[value - min];
	}

	~ColorInterpolate() {
		delete[] colorTable;
	}


private:

	static unsigned interpolate(const unsigned& cMin, const unsigned& cMax, const double& ratio) {
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		uint8_t red = ((1.0 - ratio) * qRed(cMin) + ratio * qRed(cMax));
		uint8_t green = ((1.0 - ratio) * qGreen(cMin) + ratio * qGreen(cMax));
		uint8_t blue = ((1.0 - ratio) * qBlue(cMin) + ratio * qBlue(cMax));

		unsigned color = 0x000000FF; //alpha
		color <<= 8;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;

		return color;
	}

	unsigned uniformColorCalcul(const int& value, double step, std::vector<unsigned>& colors) {

		//Include max
		if (value >= min + range) {
			return colors[colors.size() - 1];
		}

		const double v = (value - min);

		const int bin = v / step;

		const double normalized_v = (v - bin * step) / step;

		auto color = interpolate(colors[bin], colors[bin + 1], normalized_v);

		return color;
	}

	inline static std::vector<unsigned> defaultColors{
			0xFFe5f5f9,
			0xFF99d8c9,
			0xFF2ca25f,
	};

	int min;
	unsigned int range;

	unsigned* colorTable;
};