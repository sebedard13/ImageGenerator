#pragma once
#include <QFrame>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QVBoxLayout>


class MapScreen : public QFrame
{
public:
	QVBoxLayout* verticalLayout_2;
	QGraphicsView* graphicsView;
	QFrame* frame_2;
	QVBoxLayout* verticalLayout_5;
	QProgressBar* progressBar;
	QLabel* label;

	MapScreen(QWidget* parent) : QFrame(parent) {}

	void setupUi(QMainWindow* ViewRootClass);

	void retranslateUi(QMainWindow* ViewRootClass);
};

