#include "MapView.h"
#include "ViewUtils.h"

#include <iostream>
#include <QGraphicsPixmapItem>

#include "ColorInterpolate.h"
#include "../model/ThreadController.h"

MapView::MapView(MapScreen* map_screen) :mapScreen(map_screen)
{
	scene = new QGraphicsScene(mapScreen);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
	mapScreen->graphicsView->setScene(scene);
}

void MapView::loadMap(std::unique_ptr<Map> map)
{
	setMessageId("tipLoadView");
	constexpr int squareSize = 1;
	scene->clear();
	delete[] buffer;
	buffer = new uchar[map->height * map->width * 4];

	uchar* pointer = buffer;
	ColorInterpolate<int> colorInterpolate{ map->min, map->max };
	ThreadController thC = { this };
	thC.runIterationOutpout(0, map->size, [&pointer, &colorInterpolate, &map](unsigned i) {
		{
			auto color = colorInterpolate.uniformColor(map->array[i]);


			pointer[i * 4] = qBlue(color);
			pointer[i * 4 + 1] = qGreen(color);
			pointer[i * 4 + 2] = qRed(color);
			pointer[i * 4 + 3] = qAlpha(color);
		}
		});

	constexpr  int borderScene = 64;
	scene->setSceneRect(0, 0, map->width + borderScene * 2, map->height + borderScene * 2);

	auto pixmapItem = scene->addPixmap(QPixmap::fromImage(QImage(buffer, map->width, map->height, QImage::Format_ARGB32),
		Qt::ColorOnly | Qt::ThresholdDither | Qt::OrderedAlphaDither | Qt::NoFormatConversion
	));
	pixmapItem->setOffset(borderScene, borderScene);

	mapScreen->graphicsView->fitInView(0, 0, map->width + borderScene * 2, map->height + borderScene * 2, Qt::KeepAspectRatio);
	mapScreen->graphicsView->show();
	mapScreen->graphicsView->resetScale();

	map.reset();
	setPercent(0);
	setMessageId("tipNothing");
}

void MapView::setMessageId(std::string key)
{
	mapScreen->changeMessage(key);
}

void MapView::setPercent(unsigned int percent)
{
	if (percent < 0 || percent>100)
	{
		std::cout << "Non valid percent of " << percent << std::endl;
	}
	else
	{
		auto now = std::chrono::system_clock::now();
		if (percent == 100 || percent == 0 || std::chrono::duration_cast<std::chrono::milliseconds>(now - percentLastChange).count() > timeElapsedPercent) {
			percentLastChange = now;
			mapScreen->changePercent(percent);
		}
	}
}

MapView::~MapView()
{
	delete[] buffer;
}
