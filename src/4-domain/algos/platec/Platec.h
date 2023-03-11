#pragma once


#include "../Algo.h"

class Platec : public Algo {
public:
    Platec(const Platec &other) = delete;

    Platec(Platec &&other) noexcept = delete;

    Platec &operator=(const Platec &other) = delete;

    Platec &operator=(Platec &&other) noexcept = delete;

    ~Platec() = default;

    std::unique_ptr<Map> run() override;

    Platec() = default;

    Platec(size_t mapSideLength,
            float seaLevel, size_t erosionPeriod,
            float foldingRatio, size_t aggrRatioAbs,
            float aggrRatioRel, size_t numPlates,
            size_t maxCycleCount, size_t maxIterationCount,
            float mapRoughness, unsigned seed);

private:
    size_t mapSideLength = 512;
    unsigned seed = 0;
    size_t num_plates = 10;
    size_t maxCycleCount = 2;

    float mapRoughness = 0.5f;
    size_t maxIterationCount = 570;
    float seaLevel = 0.65;
    size_t erosionPeriod = 60;
    float foldingRatio = 0.001f;
    size_t aggrRatioAbs = 5000;
    float aggrRatioRel = 0.10f;
};
