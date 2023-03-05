#include "AlgoPerlinNoise.h"

#include <thread>

#include "../../../2-services/ThreadController.h"
#include "../../Mapi.h"

std::unique_ptr<Map> AlgoPerlinNoise::run() {
	output->setMessageId("tipLoadingPerlinNoise");
	Mapi* map = new Mapi(width, height);

	ThreadController thC = { output.get() };

	thC.runIterationOutput(0, map->getSize(),
		[this, map](const unsigned i) {
			{
				const auto coord = map->toCoordinate(i);
				double v = this->perlinNoise.perlin(coord.first, coord.second);
				int value = static_cast<int>((v * 256) + 256);
				map->set(i, value);
			}
		});

	map->setColors({
		0xFF000000,
		0xFFFFFFFF,
		});

	return std::unique_ptr<Map>(map);
}
