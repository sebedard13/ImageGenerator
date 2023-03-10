#pragma once

#include "Algo.h"
#include "../../2-infrastructure/RandomEngine.h"

class RandomVoronoi : public Algo {

public:
    RandomVoronoi(unsigned numberPoints, unsigned int width, unsigned int height, unsigned seed);

    RandomVoronoi(const RandomVoronoi &other) = delete;

    RandomVoronoi(RandomVoronoi &&other) noexcept = delete;

    RandomVoronoi &operator=(const RandomVoronoi &other) = delete;

    RandomVoronoi &operator=(RandomVoronoi &&other) noexcept = delete;

    ~RandomVoronoi() override = default;

    std::unique_ptr<Map> run() override;

    RandomEngine rand;
private:
    const unsigned numberPoints;
    const unsigned width;
    const unsigned height;
};
