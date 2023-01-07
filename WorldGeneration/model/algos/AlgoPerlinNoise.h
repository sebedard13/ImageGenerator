#pragma once
#include "Algo.h"

class AlgoPerlinNoise final : public Algo
{
public:
	AlgoPerlinNoise(unsigned width, unsigned height, unsigned cellSize, unsigned octaves, double persistence)
		: width(width),
		height(height),
		cellSize(cellSize),
		octaves(octaves),
		persistence(persistence)
	{
	}

	std::unique_ptr<Map> run() override;
	~AlgoPerlinNoise() override = default;
	const unsigned int width;
	const unsigned int height;

	const unsigned int cellSize;
	const unsigned int octaves;
	const double persistence; //0 to 1




};
