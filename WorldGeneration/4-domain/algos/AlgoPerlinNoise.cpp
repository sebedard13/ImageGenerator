#include "AlgoPerlinNoise.h"

#include <thread>

#include "../../2-services/ThreadController.h"

std::unique_ptr<Map> AlgoPerlinNoise::run()
{
	output->setMessageId("tipLoadingPerlinNoise");
	Map* map = new Map(width, height);

	ThreadController thC = { output.get() };

	thC.runIterationOutput(0, map->size,
		[this, map](const unsigned i)
		{
			{
				const auto coord = map->toCoordinate(i);
				double v = this->perlinNoise.perlin(coord.first, coord.second);
				int value = static_cast<int>((v * 256) + 256);
				if (value < 0)
				{
					int a = 0;
				}
				map->set(i, value);
			}
		});

	return std::unique_ptr<Map>(map);
}
