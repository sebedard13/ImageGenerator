#pragma once
#include <QAction>
#include <qboxlayout.h>
#include <QFrame>
#include <QTabWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QPushButton>

#include "MapScreen.h"
#include "tab/TabAlgo.h"
#include "tab/TabPerlinNoise.h"


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

	std::vector<std::unique_ptr<TabAlgo>> tabs{};

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