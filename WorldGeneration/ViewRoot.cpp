#include "ViewRoot.h"

#include <iostream>

#include "ViewUtils.h"

void ViewRootClass::setupUi(QMainWindow* ViewRootClass)
{
	if (ViewRootClass->objectName().isEmpty())
		ViewRootClass->setObjectName("ViewRootClass");
	ViewRootClass->resize(1228, 818);
	ViewRootClass->setLayoutDirection(Qt::LeftToRight);
	actionSauvegarder = new QAction(ViewRootClass);
	actionSauvegarder->setObjectName("actionSauvegarder");
	actionSauvegarder->setIconVisibleInMenu(true);
	actionCharger = new QAction(ViewRootClass);
	actionCharger->setObjectName("actionCharger");
	actionCharger->setCheckable(false);
	actionCharger->setIconVisibleInMenu(true);
	actionQuiter = new QAction(ViewRootClass);
	actionQuiter->setObjectName("actionQuiter");
	actionQuiter->setIconVisibleInMenu(true);
	actionVoir = new QAction(ViewRootClass);
	actionVoir->setObjectName("actionVoir");
	centralWidget = new QWidget(ViewRootClass);
	centralWidget->setObjectName("centralWidget");
	centralWidget->setEnabled(true);
	QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
	centralWidget->setSizePolicy(sizePolicy);
	centralWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
	horizontalLayout_2 = new QHBoxLayout(centralWidget);
	horizontalLayout_2->setSpacing(6);
	horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
	horizontalLayout_2->setObjectName("horizontalLayout_2");
	horizontalLayout_2->setContentsMargins(9, -1, -1, 4);
	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(20);
	horizontalLayout->setObjectName("horizontalLayout");
	frame = new QFrame(centralWidget);
	frame->setObjectName("frame");
	verticalLayout = new QVBoxLayout(frame);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setObjectName("verticalLayout");
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	tabWidget = new QTabWidget(frame);
	tabWidget->setObjectName("tabWidget");
	tabWidget->setEnabled(true);
	QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
	tabWidget->setSizePolicy(sizePolicy1);
	tabWidget->setMinimumSize(QSize(200, 0));
	tabWidget->setAutoFillBackground(true);

	//Tab 1
	tab = new TabPerlinNoise();
	tab->setupUi(ViewRootClass);
	tabs.push_back(tab);
	tabWidget->addTab(tab, QString());
	//Tab 2

	tab_2 = new QWidget();


	verticalLayout->addWidget(tabWidget);

	frame1 = new QFrame(frame);
	frame1->setObjectName("frame1");
	frame1->setAutoFillBackground(true);
	frame1->setFrameShape(QFrame::StyledPanel);
	frame1->setFrameShadow(QFrame::Plain);
	verticalLayout_4 = new QVBoxLayout(frame1);
	verticalLayout_4->setSpacing(6);
	verticalLayout_4->setContentsMargins(11, 11, 11, 11);
	verticalLayout_4->setObjectName("verticalLayout_4");
	verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
	verticalLayout_4->setContentsMargins(5, 5, 5, 5);
	btnGenerate = new QPushButton(frame1);
	btnGenerate->setObjectName("btnGenerate");
	QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(btnGenerate->sizePolicy().hasHeightForWidth());
	btnGenerate->setSizePolicy(sizePolicy2);

	verticalLayout_4->addWidget(btnGenerate);


	verticalLayout->addWidget(frame1);


	horizontalLayout->addWidget(frame);

	frame2 = new MapScreen(centralWidget);
	frame2->setupUi(ViewRootClass);




	horizontalLayout->addWidget(frame2);


	horizontalLayout_2->addLayout(horizontalLayout);

	ViewRootClass->setCentralWidget(centralWidget);
	menuBar = new QMenuBar(ViewRootClass);
	menuBar->setObjectName("menuBar");
	menuBar->setGeometry(QRect(0, 0, 1228, 22));
	menusfas = new QMenu(menuBar);
	menusfas->setObjectName("menusfas");
	menusfas->setToolTipsVisible(false);
	menuA_propos = new QMenu(menuBar);
	menuA_propos->setObjectName("menuA_propos");
	menuA_propos->setTearOffEnabled(false);
	menuA_propos->setSeparatorsCollapsible(false);
	menuA_propos->setToolTipsVisible(false);
	ViewRootClass->setMenuBar(menuBar);
	mainToolBar = new QToolBar(ViewRootClass);
	mainToolBar->setObjectName("mainToolBar");
	ViewRootClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
	statusBar = new QStatusBar(ViewRootClass);
	statusBar->setObjectName("statusBar");
	ViewRootClass->setStatusBar(statusBar);

	menuBar->addAction(menusfas->menuAction());
	menuBar->addAction(menuA_propos->menuAction());
	menusfas->addAction(actionSauvegarder);
	menusfas->addAction(actionCharger);
	menusfas->addAction(actionQuiter);
	menuA_propos->addAction(actionVoir);

	retranslateUi(ViewRootClass);
	QObject::connect(btnGenerate, &QAbstractButton::released, dynamic_cast<const ViewRoot*>(ViewRootClass), &ViewRoot::clickGenerate);

	tabWidget->setCurrentIndex(0);


	QMetaObject::connectSlotsByName(ViewRootClass);
} // setupUi

void ViewRootClass::retranslateUi(QMainWindow* ViewRootClass)
{
	ViewRootClass->setWindowTitle(ViewsUtils::local("mainWindowName"));
	actionSauvegarder->setText(ViewsUtils::local("btnSave"));
	actionCharger->setText(ViewsUtils::local("btnLoad"));
	actionQuiter->setText(ViewsUtils::local("btnQuit"));
	actionVoir->setText(ViewsUtils::local("btnSeeAbout"));

	tabWidget->setTabText(tabWidget->indexOf(tab), ViewsUtils::local("algo1Name"));

	tabWidget->setTabText(tabWidget->indexOf(tab_2), ViewsUtils::local("algo2Name"));
	btnGenerate->setText(ViewsUtils::local("btnGenerateMap"));

	menusfas->setTitle(ViewsUtils::local("btnFile"));
	menuA_propos->setTitle(ViewsUtils::local("btnAbout"));

	tab->retranslateUi(ViewRootClass);
	frame2->retranslateUi(ViewRootClass);
} // retranslateUi
void ViewRoot::clickGenerate()
{
	int index = ui.tabWidget->currentIndex();
	ui.tabs[index]->handleGenerate();
}

ViewRoot::ViewRoot(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ViewRoot::~ViewRoot()
{}
