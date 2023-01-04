#include "GeneratePerlinNoise.h"

#include "../../controller/Controller.h"
#include "../../controller/commands/DoAlgo.h"
#include "../../model/algos/DistanceFromCenter.h"

void GeneratePerlinNoise::handleGenerate()
{
	Controller::execute(std::make_unique<DoAlgo>(std::make_unique<DistanceFromCenter>()));
}
