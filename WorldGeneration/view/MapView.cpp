#include "MapView.h"

#include <iostream>

void MapView::loadMap(const int* array[])
{
	const int squareSize = 5;
	const int tileSize = 500;

	QGraphicsScene* scene = new QGraphicsScene(mapScreen);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	QPen pen = QPen(QColor(Qt::black));
	QBrush brush = QBrush(QColor(Qt::blue));
	scene->setBackgroundBrush(QBrush(QColor(Qt::black)));

	setMessageId("tipLoadView");

	for (int i = 0; i < tileSize; ++i)
	{
		for (int j = 0; j < tileSize; ++j)
		{
			scene->addRect(i * squareSize, j * squareSize, squareSize, squareSize, pen, brush);
		}
		double percent = (i / static_cast<double>(tileSize)) * 100;
		setPercent(percent);
	}
	std::cout << "yes" << std::endl;

	setPercent(100);

	mapScreen->graphicsView->setScene(scene);
	mapScreen->graphicsView->show();
	setPercent(0);
	setMessageId("tipNothing");

}

void MapView::setMessageId(std::string key)
{
	mapScreen->changeMessage(key);
}

void MapView::setPercent(int percent)
{
	if (percent < 0 || percent>100)
	{
		std::cout << "Non valid percent" << std::endl;
	}
	else
	{
		mapScreen->changePercent(percent);
	}
}
