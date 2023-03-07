#include "Platec.h"
#include "Lithosphere.h"
#include "GenerationController.h"
#include "PlatecMap.h"
#include "../../../1-foundation/MathUtils.h"

std::unique_ptr<Map> Platec::run() {
    srand(seed);
    Lithosphere* lithos = new Lithosphere(mapSideLength,
    seaLevel,
    erosionPeriod,
    foldingRatio,
    aggrRatioAbs,
    aggrRatioRel);
    lithos->createPlates(num_plates);

    GenerationController* world = new GenerationController(lithos, maxCycleCount, maxIterationCount);

    while (world->getIsRunning()){
        world->update();
        output->setPercent(percent(world->getIteration(),(unsigned) maxIterationCount));
    }

    PlatecMap* map = new PlatecMap(mapSideLength,mapSideLength);

    map->array.swap(lithos->freeTopography());
    return std::unique_ptr<Map>(map);
}

Platec::Platec(size_t mapSideLength, float seaLevel, size_t erosionPeriod, float foldingRatio, size_t aggrRatioAbs,
               float aggrRatioRel, size_t numPlates, size_t maxCycleCount, size_t maxIterationCount,unsigned seed)
        : mapSideLength(mapSideLength),
          seaLevel(seaLevel),
          erosionPeriod(erosionPeriod),
          foldingRatio(foldingRatio),
          aggrRatioAbs(aggrRatioAbs),
          aggrRatioRel(aggrRatioRel),
          num_plates(numPlates),
          maxCycleCount(maxCycleCount),
          maxIterationCount(maxIterationCount),
          seed(seed)
          {}
