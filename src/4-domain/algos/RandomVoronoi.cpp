#include "RandomVoronoi.h"
#include "vector"
#include "../Coord.h"
#include "../../1-foundation/MathUtils.h"
#include "../Mapi.h"

RandomVoronoi::RandomVoronoi(const unsigned numberPoints, const unsigned width, const unsigned height,
	const unsigned seed)
	: numberPoints(numberPoints),
	width(width),
	height(height) {

	std::srand(seed);

}

void swap_erase(std::vector<Coord>& vector, unsigned pos)
{
	const Coord tmp = vector[vector.size() - 1];
	vector[pos] = tmp;
	vector.pop_back();
}

std::unique_ptr<Map> RandomVoronoi::run() {
	//Generate points
	output->setMessageId("tipLoadingRandomVoronoi");
	Mapi* map = new Mapi(width, height);
	Coord::setSize(width, height);

	unsigned pointsDone = 0;
	std::vector<Coord> startPoints(numberPoints);
	for (unsigned i = 0; i < startPoints.size(); i++) {
		startPoints[i] = Coord(std::rand() % width, std::rand() % height);
		if (map->get(startPoints[i]) == 0) {
			map->set(startPoints[i], i + 1);
			pointsDone++;
		}
		else {
			i--;//loop back to find other points
		}
	}
	std::vector<std::vector<Coord>> pointsToFill(numberPoints);

	std::vector<Coord> directions{
			Coord(0, 1),
			Coord(1, 0),
			Coord(0, -1),
			Coord(-1, 0),
	};



	for (int i = 0; i < startPoints.size(); ++i) {
		std::vector<Coord>& currentList = pointsToFill[i];

		for (auto& d : directions) {
			const Coord coord = startPoints[i] + d;
			if (map->get(coord) == 0) {
				currentList.emplace_back(coord);
			}
		}
	}

	bool hasChange;
	unsigned modulo = map->getSize() / 256;
	do {
		hasChange = false;
		for (int i = 0; i < startPoints.size(); ++i) {
			std::vector<Coord>& currentList = pointsToFill[i];

			auto index = currentList.size();
			while (index >= currentList.size() && !currentList.empty()) {

				auto tmpIndex = std::rand() % currentList.size();
				if (map->get(currentList[tmpIndex]) == 0) {
					index = tmpIndex;
				}
				else {
					swap_erase(currentList, tmpIndex);
				}
			}
			if (index < currentList.size()) {
				Coord changedCoord = currentList[index];

				map->set(changedCoord, i + 1);
				hasChange = true;
				pointsDone++;

				for (auto& d : directions) {
					const Coord coord = changedCoord + d;
					if (map->get(coord) == 0) {
						currentList.emplace_back(coord);
					}
				}
				swap_erase(currentList, index);
			}
			if (!hasChange)
			{
				int a = 0;
			}
		}

		if (pointsDone % modulo == 0) {
			output->setPercent(percent(pointsDone, map->getSize()));
		}


	} while (hasChange);

	output->setMessageId("tipNothing");
	return std::unique_ptr<Map>(map);
}


