#include "GeneratePerlinNoise.h"

#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/DoAlgo.h"
#include "../../4-domain/algos/AlgoPerlinNoise.h"

void GeneratePerlinNoise::handleGenerate() {
    constexpr int sizes[5]{100, 500, 1000, 2500, 5000};
    const int sizeIndex = tabPerlinNoise->sizeComboBox->currentIndex();

    auto algo = std::make_unique<AlgoPerlinNoise>(sizes[sizeIndex], sizes[sizeIndex],
                                                  tabPerlinNoise->cellSizeInput->getValue(),
                                                  tabPerlinNoise->octavesInput->getValue(),
                                                  tabPerlinNoise->persistenceInput->getValue(),
                                                  tabPerlinNoise->seedInput->getValue()
    );

    Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}
