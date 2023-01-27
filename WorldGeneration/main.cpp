#include "6-view/ViewRoot.h"
#include "3-infrastructure/Localization.h"
#include "Windows.h"
#include "5-controller/Controller.h"
#include "4-domain/algos/DistanceFromCenter.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);//Console en utf-8
	Localization::setLanguage("fr");
    std::cout << "oui"<<std::endl;
	QApplication a(argc, argv);
	ViewRoot w;
	w.show();

	const auto map = w.getMainMapView();

	Controller::setUp(map);

	return a.exec();
}
