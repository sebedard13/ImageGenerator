#pragma once
#include "TabAlgo.h"
#include "TabPerlinNoise.h"

class GeneratePerlinNoise : public TabAlgo
{
public:
	explicit GeneratePerlinNoise(TabPerlinNoise* tab_perlin_noise)
		: tabPerlinNoise(tab_perlin_noise) {}

	GeneratePerlinNoise(const GeneratePerlinNoise& other) = delete;
	GeneratePerlinNoise(GeneratePerlinNoise&& other) noexcept = delete;
	GeneratePerlinNoise& operator=(const GeneratePerlinNoise& other) = delete;
	GeneratePerlinNoise& operator=(GeneratePerlinNoise&& other) noexcept = delete;
	~GeneratePerlinNoise() = default;

	void handleGenerate() final;

private:
	TabPerlinNoise* tabPerlinNoise;
};

