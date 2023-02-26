#pragma once

#include "Algo.h"

class DiamondSquare: public Algo {
public:
    DiamondSquare(const DiamondSquare &other) = delete;

    DiamondSquare(DiamondSquare &&other) noexcept = delete;

    DiamondSquare &operator=(const DiamondSquare &other) = delete;

    DiamondSquare &operator=(DiamondSquare &&other) noexcept = delete;

    DiamondSquare(const unsigned size, const unsigned seed, const double roughness);

    std::unique_ptr<Map> run() override;

    ~DiamondSquare() override = default;

private:
    const double roughness;
    const unsigned size;
};
