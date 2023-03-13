#include "DoAlgo.h"

DoAlgo::DoAlgo(std::unique_ptr<Algo> algo) {
    this->algo.swap(algo);
}

void DoAlgo::execute(const std::shared_ptr<MapView>& mapView) {
    algo->setOutput(mapView);

    std::unique_ptr<Map> map = algo->run();

    mapView->setMessageId("tipLoadView");
    mapView->loadMap(map);
    map.reset();
    mapView->setPercent(0);
    mapView->setMessageId("tipNothing");
}
