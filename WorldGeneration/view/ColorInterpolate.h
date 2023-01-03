#pragma once
#include <qcolor.h>

template<typename T>
class ColorInterpolate
{

public:
	ColorInterpolate(T const& min, T const& max) : min(min), range(max - min), step(range / (defaultColors.size() - 1))
	{
		this->colors = defaultColors;
	}

	ColorInterpolate(const  T& min, const  T& max, std::vector<QColor>& colors) : min(min), range(max - min), step(range / (colors.size() - 1))
	{
		this->colors = std::move(colors);
	}


	QColor uniformColor(const  T& value)
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

	static QColor interpolate(const QColor& cMin, const QColor& cMax, const double& ratio)
	{
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		int red = ((1.0 - ratio) * cMin.red() + ratio * cMax.red());
		int green = ((1.0 - ratio) * cMin.green() + ratio * cMax.green());
		int blue = ((1.0 - ratio) * cMin.blue() + ratio * cMax.blue());

		return { red, green, blue };
	}

	inline static std::vector<QColor> defaultColors{
		QColor(229,245,249),
		QColor(153,216,201),
		QColor(44,162,95)
	};

	double const min, range, step;
	std::vector<QColor> colors{};


};


template<>
class ColorInterpolate<int>
{

public:
	ColorInterpolate(int const& min, int const& max) : min(min), range(max - min), step(range / (defaultColors.size() - 1))
	{
		this->colors = defaultColors;
	}

	ColorInterpolate(const  int& min, const  int& max, std::vector<QColor>& colors) : min(min), range(max - min), step(range / (colors.size() - 1))
	{
		this->colors = std::move(colors);
	}


	QColor uniformColor(const  int& value)
	{
		const auto pair = colorTable.find(value);
		if (pair != colorTable.end())
		{
			return pair->second;
		}

		//Include max
		if (value == min + range)
		{
			auto& color = colors[colors.size() - 1];
			colorTable.insert(std::pair(value, color));
			return color;
		}

		const int v = (value - min);

		const int bin = std::floor(static_cast<double> (v) / step);

		const double normalized_v = (v - bin * step) / step;

		auto color = interpolate(colors[bin], colors[bin + 1], normalized_v);
		colorTable.insert(std::pair(value, color));
		return color;
	}


private:

	static QColor interpolate(const QColor& cMin, const QColor& cMax, const double& ratio)
	{
		if (ratio <= 0.0) { return cMin; }
		if (ratio >= 1.0) { return cMax; }

		int red = ((1.0 - ratio) * cMin.red() + ratio * cMax.red());
		int green = ((1.0 - ratio) * cMin.green() + ratio * cMax.green());
		int blue = ((1.0 - ratio) * cMin.blue() + ratio * cMax.blue());

		return { red, green, blue };
	}

	inline static std::vector<QColor> defaultColors{
		QColor(229,245,249),
		QColor(153,216,201),
		QColor(44,162,95)
	};

	double const min, range, step;
	std::vector<QColor> colors{};

	std::unordered_map<int, QColor> colorTable{};


};

