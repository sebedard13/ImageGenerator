#include "RandomVoronoi.h"
#include "vector"
#include "../Coord.h"

RandomVoronoi::RandomVoronoi(const unsigned numberPoints, const unsigned width, const unsigned height,
                             const unsigned seed)
        : numberPoints(numberPoints),
          width(width),
          height(height) {

    std::srand(seed);

}


std::unique_ptr<Map> RandomVoronoi::run() {
    //Generate points
    Map *map = new Map(width, height);
    Coord::setSize(width, height);

    std::vector<Coord> startPoints(numberPoints);
    for (unsigned i = 0; i < startPoints.size(); i++) {
        startPoints[i] = Coord(std::rand() % width, std::rand() % height);
        if (map->get(startPoints[i]) == 0) {
            map->set(startPoints[i], i + 1);
        } else {
            i--;//loop back to find other points
        }
    }
    std::vector<std::list<Coord>> pointsToFill(numberPoints);

    std::vector<Coord> directions{
            Coord(0, 1),
            Coord(1, 0),
            Coord(0, -1),
            Coord(-1, 0),
    };


    for (int i = 0; i < startPoints.size(); ++i) {
        std::list<Coord> &currentList = pointsToFill[i];

        for (auto &d: directions) {
            const Coord coord = startPoints[i] + d;
            if (map->get(coord) == 0) {
                currentList.emplace_back(coord);
            }
        }
    }

    bool hasChange;
    do {
        hasChange = false;
        for (int i = 0; i < startPoints.size(); ++i) {
            std::list<Coord> &currentList = pointsToFill[i];

            auto index = currentList.end();
            while (index == currentList.end() && !currentList.empty()){

                auto tmpIndex = std::rand() %currentList.size();
                auto iterator = currentList.begin();
                std::advance(iterator, tmpIndex);
                if(map->get(*iterator) == 0){
                    index = iterator;
                }
                else{
                    currentList.erase(iterator);
                }
            }
            if(index != currentList.end()){
                Coord changedCoord = *index;
                currentList.erase(index);

                map->set(changedCoord, i+1);
                hasChange=true;


                for (auto &d: directions) {
                    const Coord coord = changedCoord + d;
                    if (map->get(coord) == 0) {
                        currentList.emplace_back(coord);
                    }
                }
            }
        }

    } while (hasChange);

    return std::unique_ptr<Map>(map);
}

