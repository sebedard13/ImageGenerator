#include "DoAlgo.h"

DoAlgo::DoAlgo(std::unique_ptr<Algo> algo) {
    this->algo.swap(algo);
}

void DoAlgo::execute(const std::shared_ptr<MapView> &mapView) {
    algo->setOutput(mapView);
    mapView->loadMap(algo->run());
}
