#include <iostream>

#include "ViewRoot.h"
#include <QtWidgets/QApplication>

#include "Localization.h"

int main(int argc, char* argv[])
{
	Localization::setLanguage("fr");
	QApplication a(argc, argv);
	ViewRoot w;
	w.show();

	std::wcout << Localization::get("localizationTest") << std::endl;
	std::wcout << Localization::get("localizationTestFaux") << std::endl;;

	return a.exec();
}
