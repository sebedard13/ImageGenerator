#include "view/ViewRoot.h"
#include <QtWidgets/QApplication>

#include "Localization.h"
#include "Windows.h"

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);//Console en utf-8
	Localization::setLanguage("fr");
	QApplication a(argc, argv);
	ViewRoot w;
	w.show();

	auto map = w.getMainMapView();
	map->setMessageId("tipLoadArray");
	const int* array[100 * 100] = {};

	map->loadMap(array);


	return a.exec();
}
