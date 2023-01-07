#include "GeneratePerlinNoise.h"

#include "../../controller/Controller.h"
#include "../../controller/commands/DoAlgo.h"
#include "../../model/algos/AlgoPerlinNoise.h"

void GeneratePerlinNoise::handleGenerate()
{
	constexpr int sizes[5]{ 100,500,1000,2500,5000 };
	const int sizeIndex = tabPerlinNoise->sizeComboBox->currentIndex();

	auto algo = std::make_unique<AlgoPerlinNoise>(sizes[sizeIndex], sizes[sizeIndex],
		tabPerlinNoise->cellSizeInput->getValue(),
		tabPerlinNoise->octavesInput->getValue(),
		tabPerlinNoise->persistenceInput->getValue());

	Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}
