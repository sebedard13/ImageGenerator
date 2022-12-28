#pragma once
#include <string>

#include "MapScreen.h"

class MapView
{
private:
	MapScreen* mapScreen;
public:
	MapView(MapScreen* map_screen) :mapScreen(map_screen) {}
	void loadMap(const int* array[]);
	void setMessageId(std::string key);
	void setPercent(int percent);

};

