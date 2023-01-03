#include "view/ViewRoot.h"
#include <QtWidgets/QApplication>

#include "Localization.h"
#include "Map.h"
#include "Windows.h"

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);//Console en utf-8
	Localization::setLanguage("fr");
	QApplication a(argc, argv);
	ViewRoot w;
	w.show();

	auto map = w.getMainMapView();
	Map mapArray = Map(2000, 2000);

	mapArray.forAll([&mapArray](int x, int y, int v)-> int {


		//Assign

		int halfH = mapArray.height / 2;
		int halfW = mapArray.width / 2;

		int diffx = std::abs(halfW - x);
		int diffy = std::abs(halfH - y);

		return diffx + diffy;

	});

	map->loadMap(mapArray);



	return a.exec();
}
