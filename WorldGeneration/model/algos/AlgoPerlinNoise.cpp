#include "AlgoPerlinNoise.h"

#include "../PerlinNoise.h"



std::unique_ptr<Map> AlgoPerlinNoise::run()
{
	output->setMessageId("tipLoadingPerlinNoise");
	Map* map = new Map(width, height);

	int m = map->size / 128;

	for (unsigned i = 0; i < map->size; ++i)
	{
		const auto coord = map->toCoordinate(i);
		double v = octavesPerlin(static_cast<double>(coord.first) / cellSize, static_cast<double>(coord.second) / cellSize, 0.0, octaves, persistence);
		map->set(i, static_cast<int>((v * 256) + 256));
		if (i > 256)
		{
			int a = 1;
		}

		if (i % m == 0)
		{
			output->setPercent(percent(i, map->size));
		}
	}


	return std::unique_ptr<Map>(map);
}
