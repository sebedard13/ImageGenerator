#include "Platec.h"
#include "Lithosphere.h"
#include "GenerationController.h"
#include "PlatecMap.h"
#include "../../../1-foundation/MathUtils.h"

std::unique_ptr<Map> Platec::run() {
    Lithosphere lithos = Lithosphere(mapSideLength,
                                     seaLevel,
                                     erosionPeriod,
                                     foldingRatio,
                                     aggrRatioAbs,
                                     aggrRatioRel,
                                     mapRoughness
    );
    Lithosphere::rand = RandomEngine(seed);
    Plate::rand = RandomEngine(seed / 2); //Change number without going out of bound


    GenerationController world = GenerationController(&lithos, maxCycleCount, maxIterationCount);

    lithos.createPlates(num_plates);
    while (world.getIsRunning()) {
        world.update();
        output->setPercent(percent(world.getIteration(), (unsigned) maxIterationCount));
    }

    PlatecMap *map = new PlatecMap(mapSideLength, mapSideLength);

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
