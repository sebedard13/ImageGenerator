#pragma once

#include <memory>
#include <random>

constexpr unsigned default_seed = 0;

class RandomEngine {
public:
    RandomEngine() = default;

    RandomEngine(const unsigned seed);

    RandomEngine(const RandomEngine &other);

    RandomEngine(RandomEngine &&other) noexcept;

    RandomEngine &operator=(const RandomEngine &other);

    RandomEngine &operator=(RandomEngine &&other) noexcept;

    ~RandomEngine() = default;

    int operator()();

    unsigned getSeed() const;

    int range(int minInclude, int maxExclude);

    float range(float minInclude, float maxExclude);

private:

    std::shared_ptr<std::minstd_rand> engine = std::make_unique<std::minstd_rand>(default_seed);
    unsigned seed =default_seed;
};
