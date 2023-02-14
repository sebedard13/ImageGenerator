#include "GenerateRandomVoronoi.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/DoAlgo.h"
#include "../../4-domain/algos/RandomVoronoi.h"

GenerateRandomVoronoi::GenerateRandomVoronoi(TabRandomVoronoi *tabRandomVoronoi)
: tabRandomVoronoi(tabRandomVoronoi)
{}

void GenerateRandomVoronoi::handleGenerate() {
    constexpr int sizes[5]{100, 500, 1000, 2500, 5000};
    const int sizeIndex = tabRandomVoronoi->sizeComboBox->currentIndex();

    auto algo = std::make_unique<RandomVoronoi>(tabRandomVoronoi->nbPointsInput->getValue(),sizes[sizeIndex], sizes[sizeIndex],
                                                   tabRandomVoronoi->seedInput->getValue()
    );

    Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}
