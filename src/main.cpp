#include "6-view/ViewRoot.h"
#include "3-infrastructure/Localization.h"
#include "Windows.h"
#include "5-controller/Controller.h"
#include "5-controller/commands/DoAlgo.h"
#include "4-domain/algos/platec/Platec.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);//Console en utf-8
    Localization::setLanguage("fr");
    QApplication a(argc, argv);
    ViewRoot w;
    w.show();

    const auto map = w.getMainMapView();

    Controller::setUp(map);

    Controller::execute(std::make_unique<DoAlgo>(std::make_unique<Platec>()));

    return a.exec();
}
