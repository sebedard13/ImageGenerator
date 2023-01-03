#include "MapView.h"
#include "ViewUtils.h"

#include <iostream>

#include "ColorInterpolate.h"

void MapView::loadMap(const Map& map)
{
	const int squareSize = 5;

	QGraphicsScene* scene = new QGraphicsScene(mapScreen);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);


	scene->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));

	setMessageId("tipLoadView");

	QPixmap* pixmap = new QPixmap(map.width * squareSize, map.height* squareSize);
	QPainter* painter = new QPainter(pixmap);
	painter->setPen(Qt::NoPen);
	if (squareSize > 10) {
		QPen pen = QPen(QColor(Qt::black));
		pen.setWidth(0);
		painter->setPen(pen);
	}

	ColorInterpolate<int> colorInterpolate{map.min, map.max};

	map.forEach([&painter, &map, &colorInterpolate](int x, int y, int v)-> void{

		painter->setBrush(colorInterpolate.uniformColor(v));
		painter->drawRect(x* squareSize, y* squareSize, squareSize, squareSize);
	});
	
	
	std::cout << "yes" << std::endl;
	scene->addPixmap(*pixmap);
	mapScreen->graphicsView->setScene(scene);
	mapScreen->graphicsView->show();

	delete painter;
	delete pixmap;
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
