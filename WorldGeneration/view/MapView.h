#pragma once
#include <string>

#include "MapScreen.h"
#include "../Map.h"

class MapView
{
private:
	MapScreen* mapScreen;
	std::chrono::time_point<std::chrono::system_clock> percentLastChange = std::chrono::system_clock::now() ;
	const static unsigned short timeElapsedPercent{ 50 };
public:
	MapView(MapScreen* map_screen) :mapScreen(map_screen) {}
	void loadMap(const Map& map);
	void setMessageId(std::string key);
	void setPercent(unsigned int percent);

};

