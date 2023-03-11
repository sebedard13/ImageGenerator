#include "Platec.h"
#include "Lithosphere.h"
#include "GenerationController.h"
#include "PlatecMap.h"
#include "../../../1-foundation/MathUtils.h"
#include <thread>

std::unique_ptr<Map> Platec::run() {
    output->setMessageId("tipLoadingPlatec");
    
    Lithosphere::rand = RandomEngine(seed);
    Plate::rand = RandomEngine(seed / 2); //Change number without going out of bound


    Lithosphere lithos = Lithosphere(mapSideLength,
            seaLevel,
            erosionPeriod,
            foldingRatio,
            aggrRatioAbs,
            aggrRatioRel,
            mapRoughness
    );

    GenerationController world = GenerationController(&lithos, maxCycleCount, maxIterationCount);

    lithos.createPlates(num_plates);
    while (world.getIsRunning()) {
        world.update();

        auto* map = new PlatecMap(mapSideLength, mapSideLength);
        auto heightMap = lithos.getTopography();
        map->array = heightMap;
        std::unique_ptr<Map> ptr{map};


        output->setPercent(percent(world.getIteration() + world.getMaxIteration() * world.getCycle(),
                (unsigned) world.getMaxIteration() * world.getMaxCycle()));
        output->loadMap(ptr);
    }

    auto* map = new PlatecMap(mapSideLength, mapSideLength);

    map->array.swap(lithos.freeTopography());
    return std::unique_ptr<Map>(map);
}

Platec::Platec(size_t mapSideLength, float seaLevel, size_t erosionPeriod, float foldingRatio, size_t aggrRatioAbs,
        float aggrRatioRel, size_t numPlates, size_t maxCycleCount, size_t maxIterationCount, float mapRoughness,
        unsigned seed)
        : mapSideLength(mapSideLength),
        seaLevel(seaLevel),
        erosionPeriod(erosionPeriod),
        foldingRatio(foldingRatio),
        aggrRatioAbs(aggrRatioAbs),
        aggrRatioRel(aggrRatioRel),
        num_plates(numPlates),
        maxCycleCount(maxCycleCount),
        maxIterationCount(maxIterationCount),
        seed(seed),
        mapRoughness(mapRoughness) {}
