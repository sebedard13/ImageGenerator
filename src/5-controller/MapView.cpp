#include "MapView.h"

#include <iostream>
#include <QGraphicsPixmapItem>
#include <QString>

#include "../2-services/ThreadController.h"
#include "../2-services/SetTimeout.h"

#include <thread>
#include <chrono>

MapView::MapView(MapScreen* map_screen)
	: mapScreen(map_screen) {
	scene = new QGraphicsScene(mapScreen);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
	mapScreen->graphicsView->setScene(scene);
}

void MapView::loadMap(std::unique_ptr<Map> map) {
	setMessageId("tipLoadView");
	scene->clear();
	delete[] buffer;
	buffer = new uchar[map->height * map->width * 4];

	uchar* pointer = buffer;
	ThreadController thC = { this };
	map->prepareRender();
	thC.runIterationOutput(0, map->size, [&pointer, &map](unsigned i) {
		{
			auto color = map->render(i);

			pointer[i * 4] = qBlue(color);
			pointer[i * 4 + 1] = qGreen(color);
			pointer[i * 4 + 2] = qRed(color);
			pointer[i * 4 + 3] = qAlpha(color);
		}
		});

	constexpr int borderScene = 64;
	scene->setSceneRect(0, 0, map->width + borderScene * 2, map->height + borderScene * 2);

	image = QImage(buffer, map->width, map->height, QImage::Format_ARGB32);
	auto pixmapItem = scene->addPixmap(QPixmap::fromImage(image,
		Qt::ColorOnly | Qt::ThresholdDither | Qt::OrderedAlphaDither |
		Qt::NoFormatConversion
	));
	pixmapItem->setOffset(borderScene, borderScene);


	mapScreen->graphicsView->fitInView(0, 0, map->width + borderScene * 2, map->height + borderScene * 2,
		Qt::KeepAspectRatio);
	mapScreen->graphicsView->show();
	mapScreen->graphicsView->resetScale();

	map.reset();
	setPercent(0);
	setMessageId("tipNothing");
}

void MapView::setMessageId(const std::string& key) {
	mapScreen->changeMessage(key);
}

void MapView::setPercent(unsigned int percent) {
	if (percent > 100) {
		std::cout << "Non valid percent of " << percent << std::endl;
	}
	else {
		auto now = std::chrono::system_clock::now();
		if (percent == 100 || percent == 0 ||
			std::chrono::duration_cast<std::chrono::milliseconds>(now - percentLastChange).count() >
			timeElapsedPercent) {
			percentLastChange = now;
			mapScreen->changePercent(percent);
		}
	}
}

void MapView::saveImageAt(const std::filesystem::path& path) {
	MapView* mapView = this;
	if (image.isNull()) {
		setMessageId("saveRtnEmpty");
		setTimeout(4000, [mapView]() {
			mapView->setMessageId("tipNothing");
			});
	}
	else {
		mapView->setMessageId("saveRtnCompression");
		setTimeout(0, [mapView, path]() -> void {
			const bool result = mapView->image.save(QString::fromStdString(path.generic_string()), "PNG", -1);
		if (result) {
			mapView->setMessageId("saveRtnGood");
		}
		else {
			mapView->setMessageId("saveRtnBad");
		}
		setTimeout(4000, [mapView]() {
			mapView->setMessageId("tipNothing");
			});
			});

	}


}

MapView::~MapView() {
	delete[] buffer;
}
