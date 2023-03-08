#pragma once

#include <filesystem>
#include <string>

#include "../6-view/MapScreen.h"
#include "../4-domain/Map.h"
#include "../4-domain/Output.h"

class MapView : public Output {
private:
    MapScreen *mapScreen;
    QGraphicsScene *scene;
    QImage image;
    uchar *buffer = nullptr;
    std::chrono::time_point<std::chrono::system_clock> percentLastChange = std::chrono::system_clock::now();
    const static unsigned short timeElapsedPercent{50};
public:
    MapView(MapScreen *map_screen);

    void loadMap(std::unique_ptr<Map> map) override;

    void setMessageId(const std::string &key) override;

    void setPercent(unsigned int percent) override;

    void saveImageAt(const std::filesystem::path &path);

    ~MapView();
};