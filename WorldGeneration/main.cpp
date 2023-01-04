#include "view/ViewRoot.h"
#include <QtWidgets/QApplication>

#include "Localization.h"
#include "Map.h"
#include "Windows.h"
#include "controller/Controller.h"
#include "controller/commands/DoAlgo.h"
#include "model/algos/DistanceFromCenter.h"

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);//Console en utf-8
	Localization::setLanguage("fr");
	QApplication a(argc, argv);
	ViewRoot w;
	w.show();

	const auto map = w.getMainMapView();

	Controller::setUp(map);

	return a.exec();
}
