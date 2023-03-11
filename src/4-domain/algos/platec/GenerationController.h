#pragma once

#include "Lithosphere.h"

class GenerationController {
public:
    GenerationController(Lithosphere* lithosphere, unsigned maxCycleCount, unsigned maxIterationCount)
            : lithosphere(lithosphere),
            maxCycle(maxCycleCount),
            maxIteration(maxIterationCount) {
    }

    GenerationController(const GenerationController &other) = delete;

    GenerationController(GenerationController &&other) noexcept = delete;

    GenerationController &operator=(const GenerationController &other) = delete;

    GenerationController &operator=(GenerationController &&other) noexcept = delete;

    ~GenerationController() = default;

    void update();

    [[nodiscard]] unsigned getMaxCycle() const {
        return maxCycle;
    }

    [[nodiscard]] unsigned getMaxIteration() const {
        return maxIteration;
    }

    [[nodiscard]] unsigned getIteration() const {
        return iteration;
    }

    [[nodiscard]] unsigned getCycle() const {
        return cycle;
    }

    [[nodiscard]] bool getIsRunning() const;

private:

    [[nodiscard]] bool isStale() const;

    [[nodiscard]] bool isContinuing() const;

    bool isRunning = true;
    Lithosphere* lithosphere;
    const unsigned maxCycle;
    const unsigned maxIteration;
    unsigned iteration = 0;
    unsigned cycle = 0;

public:

};


