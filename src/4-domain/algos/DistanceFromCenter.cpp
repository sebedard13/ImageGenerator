#include "DistanceFromCenter.h"
#include "../../1-foundation/MathUtils.h"
#include "../Mapi.h"

std::unique_ptr<Map> DistanceFromCenter::run() {
    std::unique_ptr<Mapi> map = std::make_unique<Mapi>(10000, 10000);

    int m = map->getSize() / 128;

    auto a = output;
    a->setMessageId("tipAlgoDistanceFromCenter");
    const int halfH = map->getHeight() / 2;
    const int halfW = map->getWidth() / 2;
    for (unsigned i = 0; i < map->getSize(); ++i) {
        auto coord = map->toCoordinate(i);
        const int diffx = std::abs(static_cast<int> (halfW - coord.first));
        const int diffy = std::abs(static_cast<int> (halfH - coord.second));

        if (i % m == 0) {
            a->setPercent(percent(i, map->getSize()));
        }

        map->set(i, diffx + diffy);
    }

    return map;
}
