#include "PlatecMap.h"

unsigned int PlatecMap::getWidth() const {
    return width;
}

unsigned int PlatecMap::getHeight() const {
    return height;
}

unsigned int PlatecMap::getSize() const {
    return width*height;
}

void PlatecMap::prepareRender() {
    for (int i = 0; i < colorsMap.size()-1; ++i) {
        float bottomRange = colorsMap[i].first;
        float topRange = colorsMap[i + 1].first;
        std::vector<unsigned int> colors{colorsMap[i].second, colorsMap[i + 1].second};
        colorInterpolates.emplace_back(bottomRange, topRange, colors);
    }
}

unsigned int PlatecMap::render(const unsigned int &indexValue) const {
    float value = array[indexValue];

    if(value<colorsMap[0].first){
        return colorsMap[0].second;
    }
    for (int i = 1; i < colorsMap.size(); ++i) {
        if(value < colorsMap[i].first){
            return  colorInterpolates[i-1].uniformColor(value);
        }
    }
    if(value>colorsMap[colorsMap.size()-1].first){
        return colorsMap[colorsMap.size()-1].second;
    }

    return 0;
}

PlatecMap::PlatecMap(const unsigned int width, const unsigned int height)
        : width(width),
          height(height) {}
