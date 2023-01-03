#include "MapView.h"
#include "ViewUtils.h"

#include <iostream>
#include <QGraphicsPixmapItem>

#include "ColorInterpolate.h"

void MapView::loadMap(const Map& map)
{
	const int squareSize = 1;

	QGraphicsScene* scene = new QGraphicsScene(mapScreen);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);


	scene->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));

	setMessageId("tipLoadView");
	
	uchar* buffer = new uchar[map.height * map.width * 4];
	
	if (squareSize > 10) {
		QPen pen = QPen(QColor(Qt::black));
		pen.setWidth(0);
	}

	ColorInterpolate<int> colorInterpolate{map.min, map.max};

	const int m = (map.size / 128);
	for (unsigned int i = 0; i < map.size; i++)
	{
		auto color = colorInterpolate.uniformColor(map.array[i]);


		buffer[i * 4] = qBlue(color);
		buffer[i * 4 + 1] = qGreen(color);
		buffer[i * 4 + 2] = qRed(color);
		buffer[i * 4 + 3] = qAlpha(color);
		
		if (i % m == 0) {
			setPercent((i * 100) / map.size);
		}
		

	}

	const int borderScene = 64;
	scene->setSceneRect(0, 0, map.width + borderScene*2, map.height + borderScene*2);
	
	auto pixmapItem = scene->addPixmap(QPixmap::fromImage(QImage(buffer, map.width, map.height, QImage::Format_ARGB32), 
		Qt::ColorOnly | Qt::ThresholdDither| Qt::OrderedAlphaDither|Qt::NoFormatConversion
	));
	pixmapItem->setOffset(borderScene, borderScene);

	
	
	mapScreen->graphicsView->setScene(scene);
	mapScreen->graphicsView->show();
	mapScreen->graphicsView->fitInView(0, 0, map.width + borderScene * 2, map.height + borderScene * 2, Qt::KeepAspectRatio);
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
		std::cout << "Non valid percent" << std::endl;
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
