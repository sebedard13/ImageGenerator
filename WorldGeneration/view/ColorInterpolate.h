#pragma once
#include <qcolor.h>

template<typename T>
class ColorInterpolate
{

public:
	ColorInterpolate(const  T& min, const  T& max, std::vector<QRgb>& colors = defaultColors) : min(min), range(max - min), step(range / (colors.size() - 1))
	{
		this->colors = std::move(colors);
	}


	QRgb uniformColor(const  T& value)
	{
		//Include max
		if (value == min + range)
		{
			return colors[colors.size() - 1];
		}

		const double v = (value - min);

		const int bin = v / step;

		const double normalized_v = (v - bin * step) / step;

		return interpolate(colors[bin], colors[bin + 1], normalized_v);
	}


private:

	static QRgb interpolate(const QRgb& cMin, const QRgb& cMax, const double& ratio)
	{
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		uint8_t red = ((1.0 - ratio) * qRed(cMin) + ratio * qRed(cMax));
		uint8_t green = ((1.0 - ratio) * qGreen(cMin) + ratio * qGreen(cMax));
		uint8_t blue = ((1.0 - ratio) * qBlue(cMin) + ratio * qBlue(cMax));

		QRgb color = 0x000000FF; //alpha
		color <<= 8;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;

		return color;
	}

	inline static std::vector<QRgb> defaultColors{
		0xFFe5f5f9,
		0xFF99d8c9,
		0xFF2ca25f,
	};

	double const min, range, step;
	std::vector<QRgb> colors{};


};


//For unsigned
template<>
class ColorInterpolate<int>
{

public:
	ColorInterpolate(const  int& min, const  int& max, std::vector<QRgb>& colors = defaultColors) : min(min), range(max - min)
	{
		colorTable = new QRgb[range + 1];
		double step = range / (colors.size() - 1);
		for (auto i	= 0; i < range; i++)
		{
			colorTable[i] = uniformColorCalcul(i + min, step, colors);
		}
	}


	QRgb uniformColor(const int& value)
	{
		return colorTable[value - min];
	}

	~ColorInterpolate() {
		delete[] colorTable;
	}


private:

	static QRgb interpolate(const QRgb& cMin, const QRgb& cMax, const double& ratio)
	{
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		uint8_t red = ((1.0 - ratio) * qRed(cMin) + ratio * qRed(cMax));
		uint8_t green = ((1.0 - ratio) * qGreen(cMin) + ratio * qGreen(cMax));
		uint8_t blue = ((1.0 - ratio) * qBlue(cMin) + ratio * qBlue(cMax));

		QRgb color = 0x000000FF; //alpha
		color <<= 8;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;

		return color;
	}

	QRgb uniformColorCalcul(const  int& value, double step, std::vector<QRgb>& colors) {

		//Include max
		if (value == min + range)
		{
			return colors[colors.size() - 1];
		}

		const double v = (value - min);

		const int bin = v / step;

		const double normalized_v = (v - bin * step) / step;

		auto color = interpolate(colors[bin], colors[bin + 1], normalized_v);

		return color;
	}

	inline static std::vector<QRgb> defaultColors{
		0xFFe5f5f9,
		0xFF99d8c9,
		0xFF2ca25f,
	};

	int const min;
	unsigned int range;

	QRgb* colorTable;
};