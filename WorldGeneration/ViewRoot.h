#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "Localization.h"
#include "MapScreen.h"
#include "TabPerlinNoise.h"


class ViewRootClass
{
public:
	QAction* actionSauvegarder;
	QAction* actionCharger;
	QAction* actionQuiter;
	QAction* actionVoir;
	QWidget* centralWidget;
	QHBoxLayout* horizontalLayout_2;
	QHBoxLayout* horizontalLayout;
	QFrame* frame;
	QVBoxLayout* verticalLayout;
	QTabWidget* tabWidget;
	TabPerlinNoise* tab;
	QWidget* tab_2;
	QFrame* frame1;
	QVBoxLayout* verticalLayout_4;
	QPushButton* btnGenerate;
	MapScreen* frame2;
	QMenuBar* menuBar;
	QMenu* menusfas;
	QMenu* menuA_propos;
	QToolBar* mainToolBar;
	QStatusBar* statusBar;

	std::vector<TabAlgo*> tabs{};

	void setupUi(QMainWindow* ViewRootClass);

	void retranslateUi(QMainWindow* ViewRootClass);

};


class ViewRoot : public QMainWindow
{
	Q_OBJECT

public:
	ViewRoot(QWidget* parent = nullptr);
	~ViewRoot();
	void clickGenerate();

private:
	ViewRootClass ui;
};