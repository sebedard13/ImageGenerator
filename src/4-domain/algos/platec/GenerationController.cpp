#include "GenerationController.h"


constexpr float RESTART_ENERGY_RATIO = 0.15;
constexpr float RESTART_SPEED_LIMIT = 2.0;
constexpr size_t NO_COLLISION_TIME_LIMIT = 10;

bool GenerationController::isStale() const {
    // If there's no continental collisions during past iterations,
// then interesting activity has ceased and we should restart.
// Also if the simulation has been going on for too long already,
// restart, because interesting stuff has most likely ended.
    return (lithosphere->getTotalVelocity() < RESTART_SPEED_LIMIT ||
            lithosphere->getSystemKineticEnergy() / lithosphere->getPeakEk() < RESTART_ENERGY_RATIO ||
            lithosphere->getLastCollCount() > NO_COLLISION_TIME_LIMIT ||
            iteration > maxIteration);
}

bool GenerationController::isContinuing() const {
    return cycle < maxCycle + !maxCycle;
}

void GenerationController::update() {
    if (isRunning) {
        if (isStale()) {
            cycle += maxCycle > 0;
            if (isContinuing()) {
                lithosphere->restart();
                lithosphere->createPlates(lithosphere->getPlateCount());
                iteration = 0;
            } else {
                lithosphere->restart();
                lithosphere->end();
                isRunning = false;
            }
        } else {
            lithosphere->update();
            iteration++;
        }
    }
}

bool GenerationController::getIsRunning() const {
    return isRunning;
}
