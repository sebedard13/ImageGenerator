#include <iostream>
#include "RandomEngine.h"

RandomEngine::RandomEngine(const RandomEngine& other) {
    engine = other.engine;
    seed = other.seed;
}

RandomEngine::RandomEngine(const unsigned int seed)
        : seed(seed) {
    engine = std::make_unique<std::minstd_rand>(seed);
}

RandomEngine::RandomEngine(RandomEngine&& other) noexcept {
    engine = other.engine;
    seed = other.seed;
}

RandomEngine& RandomEngine::operator=(const RandomEngine& other) {
    engine = other.engine;
    seed = other.seed;
    return *this;
}

RandomEngine& RandomEngine::operator=(RandomEngine&& other) noexcept {
    engine = other.engine;
    seed = other.seed;
    return *this;
}


int RandomEngine::operator()() {
    std::uniform_int_distribution<int> dist{0, RAND_MAX};
    int i = dist(*engine);
    return i;
}

unsigned RandomEngine::getSeed() const {
    return seed;
}

int RandomEngine::range(int minInclude, int maxExclude) {
    std::uniform_int_distribution<int> dist{minInclude, maxExclude - 1};
    return dist(*engine);
}

float RandomEngine::range(float minInclude, float maxExclude) {
    std::uniform_real_distribution<float> dist{minInclude, maxExclude};
    return dist(*engine);
}




