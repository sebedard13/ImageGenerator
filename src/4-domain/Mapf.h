#pragma once
#include "Map.h"


class Mapf : public Map {
public:
    Mapf(unsigned int w, unsigned int h);

    Mapf(const Mapf &other) = delete;

    Mapf(Mapf &&other) noexcept = delete;

    Mapf &operator=(const Mapf &other) = delete;

    Mapf &operator=(Mapf &&other) noexcept = delete;

    ~Mapf() = default;

    virtual unsigned int render(const unsigned int &i) const override;

    std::vector<float> array{};

    float minf = 0;
    float maxf = 0;
};
