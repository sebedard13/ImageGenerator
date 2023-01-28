#pragma once

#include "Algo.h"
#include "../perlin/PerlinNoise.h"

class AlgoPerlinNoise final : public Algo {
public:
    AlgoPerlinNoise(unsigned width, unsigned height, unsigned cellSize, unsigned octaves, double persistence,
                    unsigned seed)
            : width(width),
            height(height),
            perlinNoise(cellSize, octaves, persistence, seed) {
    }

    std::unique_ptr<Map> run() override;

    ~AlgoPerlinNoise() override = default;

    const unsigned int width;
    const unsigned int height;

    const PerlinNoise perlinNoise;
};
