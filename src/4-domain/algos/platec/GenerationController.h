#pragma once

#include "Lithosphere.h"

class GenerationController {
public:
	GenerationController(Lithosphere* lithosphere, unsigned maxCycleCount, unsigned maxIterationCount)
		: lithosphere(lithosphere),
		maxCycle(maxCycleCount),
		maxIteration(maxIterationCount)
	{
	}

	GenerationController(const GenerationController& other) = delete;
	GenerationController(GenerationController&& other) noexcept = delete;
	GenerationController& operator=(const GenerationController& other) = delete;
	GenerationController& operator=(GenerationController&& other) noexcept = delete;

	~GenerationController() = default;

	void update();

	size_t getPlateCount() const
	{
		return lithosphere->getPlateCount();
	}

	unsigned getMaxCycle() const
	{
		return maxCycle;
	}

	unsigned getMaxIteration() const
	{
		return maxIteration;
	}

	unsigned getIteration() const
	{
		return iteration;
	}

	unsigned getCycle() const
	{
		return cycle;
	}

    bool getIsRunning() const;
    bool isRunning = true;
private:

	bool isStale() const;
	bool isContinuing() const;

	Lithosphere* lithosphere;
	const unsigned maxCycle;
	const unsigned maxIteration;
	unsigned iteration = 0;
	unsigned cycle = 0;

public:

};


