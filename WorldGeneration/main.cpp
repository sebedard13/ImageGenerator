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


	return a.exec();
}
