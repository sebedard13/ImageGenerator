#pragma once
#include <string>

#include "MapScreen.h"
#include "../Map.h"

class MapView
{
private:
	MapScreen* mapScreen;
	QGraphicsScene* scene;
	uchar* buffer = nullptr;
	std::chrono::time_point<std::chrono::system_clock> percentLastChange = std::chrono::system_clock::now();
	const static unsigned short timeElapsedPercent{ 50 };
public:
	MapView(MapScreen* map_screen);

	void loadMap(std::unique_ptr<Map> map);
	void setMessageId(std::string key);
	void setPercent(unsigned int percent);
	~MapView();
};

template<typename T>
T percent(T num, T denum)
{
	while (num > 255)
	{
		num >>= 2;
		denum >>= 2;
	}

	num *= 100;

	return num / denum;
}