#include "DistanceFromCenter.h"

std::unique_ptr<Map> DistanceFromCenter::run()
{
	std::unique_ptr<Map> map = std::make_unique<Map>(10000, 10000);

	int m = map->size / 128;

	auto a = output;
	a->setMessageId("tipAlgoDistanceFromCenter");
	const int halfH = map->height / 2;
	const int halfW = map->width / 2;
	map->forAll([&map, &a, &m, &halfH, &halfW](const unsigned int& v, const unsigned int& x, const unsigned int& y, const unsigned int& i) -> int
		{
			{
				const int diffx = std::abs(static_cast<int> (halfW - x));
				const int diffy = std::abs(static_cast<int> (halfH - y));

				if (i % m == 0)
				{
					a->setPercent(percent(i, map->size));
				}

				return diffx + diffy;
			}
		}
	);

	return map;
}
