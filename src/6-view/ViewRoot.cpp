#include "ViewRoot.h"
#include <QShortcut>
#include "ViewUtils.h"
#include "../3-services/KeyBinding.h"

void ViewRootClass::setupUi(QMainWindow *ViewRootClass) {
    if (ViewRootClass->objectName().isEmpty())
        ViewRootClass->setObjectName("ViewRootClass");
    ViewRootClass->resize(1228, 818);
    ViewRootClass->setLayoutDirection(Qt::LeftToRight);
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
    tabWidget->setMinimumWidth(200);
    tabWidget->setMaximumWidth(350);
    tabWidget->setAutoFillBackground(true);

    //Tab 0
    tab0 = new TabPerlinNoise();
    tab0->setupMainUi();
    tabs.push_back(std::make_unique<GeneratePerlinNoise>(tab0));
    tabWidget->addTab(tab0, QString());

    //Tab 1
    tab1 = new TabRandomVoronoi();
    tab1->setupMainUi();
    tabs.push_back(std::make_unique<GenerateRandomVoronoi>(tab1));
    tabWidget->addTab(tab1, QString());

    //Tab 2
    tab2 = new TabDiamondSquare();
    tab2->setupMainUi();
    tabs.push_back(std::make_unique<GenerateDiamondSquare>(tab2));
    tabWidget->addTab(tab2, QString());


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
    const QKeySequence key = QKeySequence(QString::fromStdString(KeyBinding::get("btnGenerateMap")));
    btnGenerate->setShortcut(key);
    btnGenerate->setToolTip(key.toString());

    auto *shortcut = new QShortcut(key, btnGenerate, SLOT(click()));
    shortcut->setAutoRepeat(false);

    verticalLayout_4->addWidget(btnGenerate);


    verticalLayout->addWidget(frame1);


    horizontalLayout->addWidget(frame);

    mainMapScreen = new MapScreen(centralWidget);
    mainMapScreen->setupUi(ViewRootClass);

    mapView = std::make_shared<MapView>(mainMapScreen);

    horizontalLayout->addWidget(mainMapScreen);

    horizontalLayout_2->addLayout(horizontalLayout);

    ViewRootClass->setCentralWidget(centralWidget);

    ////MENU BAR
    menuBar = new MenuBar(ViewRootClass);
    menuBar->setupUi(ViewRootClass);
    ViewRootClass->setMenuBar(menuBar);




//	statusBar = new QStatusBar(ViewRootClass);
//	statusBar->setObjectName("statusBar");
//	ViewRootClass->setStatusBar(statusBar);

    retranslateUi(ViewRootClass);
    QObject::connect(btnGenerate, &QAbstractButton::clicked, dynamic_cast<const ViewRoot *>(ViewRootClass),
                     &ViewRoot::clickGenerate);

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(ViewRootClass);
} // setupUi

void ViewRootClass::retranslateUi(QMainWindow *ViewRootClass) {
    ViewRootClass->setWindowTitle(ViewsUtils::local("mainWindowName"));

    tabWidget->setTabText(tabWidget->indexOf(tab0), ViewsUtils::local("algoPerlinNoiseName"));

    tabWidget->setTabText(tabWidget->indexOf(tab1), ViewsUtils::local("algoRandomVoronoiName"));
    tabWidget->setTabText(tabWidget->indexOf(tab2), ViewsUtils::local("algoDiamondSquareName"));
    btnGenerate->setText(ViewsUtils::local("btnGenerateMap"));


    tab0->retranslateUi();
    mainMapScreen->retranslateUi();
    menuBar->retranslateUi();
} // retranslateUi
void ViewRoot::clickGenerate() {
    int index = ui.tabWidget->currentIndex();
    ui.tabs[index]->handleGenerate();
}

ViewRoot::ViewRoot(QWidget *parent)
        : QMainWindow(parent) {
    ui.setupUi(this);
}

ViewRoot::~ViewRoot() {}
