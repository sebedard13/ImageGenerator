#include "DistanceFromCenter.h"
#include "../../1-foundation/MathUtils.h"

std::unique_ptr<Map> DistanceFromCenter::run() {
    std::unique_ptr<Map> map = std::make_unique<Map>(10000, 10000);

    int m = map->size / 128;

    auto a = output;
    a->setMessageId("tipAlgoDistanceFromCenter");
    const int halfH = map->height / 2;
    const int halfW = map->width / 2;
    for (unsigned i = 0; i < map->size; ++i) {
        auto coord = map->toCoordinate(i);
        const int diffx = std::abs(static_cast<int> (halfW - coord.first));
        const int diffy = std::abs(static_cast<int> (halfH - coord.second));

        if (i % m == 0) {
            a->setPercent(percent(i, map->size));
        }

        map->set(i, diffx + diffy);
    }

    return map;
}
