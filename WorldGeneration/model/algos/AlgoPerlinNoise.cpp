#include "AlgoPerlinNoise.h"

#include <thread>

#include "../ThreadController.h"

std::unique_ptr<Map> AlgoPerlinNoise::run()
{
	output->setMessageId("tipLoadingPerlinNoise");
	Map* map = new Map(width, height);

	ThreadController thC = { output.get() };

	thC.runIterationOutpout(0, map->size,
		[this, map](const unsigned i)
		{
			{
				const auto coord = map->toCoordinate(i);
				double v = this->perlinNoise.perlin(coord.first, coord.second);
				map->set(i, static_cast<int>((v * 256) + 256));
			}
		});

	return std::unique_ptr<Map>(map);
}
