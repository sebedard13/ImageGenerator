#include "SaveImage.h"

void SaveImage::execute(const std::shared_ptr<MapView> &mapView) {
    mapView->saveImageAt(path);
}
