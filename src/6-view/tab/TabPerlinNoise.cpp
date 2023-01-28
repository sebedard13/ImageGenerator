#include "TabPerlinNoise.h"

#include <iostream>

#include "../ViewUtils.h"

void TabPerlinNoise::setupUi(QMainWindow *ViewRootClass) {
    this->setObjectName("tab");
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    this->setAutoFillBackground(false);

    verticalLayout_6 = new QVBoxLayout(this);
    verticalLayout_6->setSpacing(6);
    verticalLayout_6->setContentsMargins(11, 11, 11, 11);
    verticalLayout_6->setObjectName("verticalLayout_6");
    verticalLayout_6->setContentsMargins(0, 0, 0, -1);
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidgetResizable(true);
    scrollArea->setAutoFillBackground(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 192, 666));
    mainLayout = new QVBoxLayout(scrollAreaWidgetContents);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(9, -1, -1, -1);
    tile = new QLabel(scrollAreaWidgetContents);
    tile->setObjectName("tile");
    QFont font;
    font.setPointSize(11);
    tile->setFont(font);

    mainLayout->addWidget(tile);

    sizeContainer = new QWidget(scrollAreaWidgetContents);
    sizeContainer->setObjectName("sizeContainer");

    sizeContainerLayout = new QVBoxLayout(sizeContainer);
    sizeContainerLayout->setSpacing(5);
    sizeContainerLayout->setContentsMargins(11, 11, 11, 11);
    sizeContainerLayout->setObjectName("sizeContainerLayout");
    sizeContainerLayout->setContentsMargins(0, 0, 0, 0);
    sizeLabel = new QLabel(sizeContainer);
    sizeLabel->setObjectName("sizeLabel");
    sizeContainerLayout->addWidget(sizeLabel);
    sizeComboBox = new QComboBox(sizeContainer);
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->setCurrentIndex(1);
    sizeComboBox->setObjectName("sizeComboBox");
    sizeContainerLayout->addWidget(sizeComboBox);

    mainLayout->addWidget(sizeContainer);

    seedInput = new InputInteger("labelSeed", 0, 0);
    mainLayout->addWidget(seedInput);

    cellSizeInput = new InputInteger("labelCellSize", 24, 1, 5000);
    mainLayout->addWidget(cellSizeInput);

    octavesInput = new InputInteger("labelOctaves", 1, 1, 24);
    mainLayout->addWidget(octavesInput);

    persistenceInput = new InputDouble("labelPersistence", 0.8);
    mainLayout->addWidget(persistenceInput);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    mainLayout->addItem(verticalSpacer);

    scrollArea->setWidget(scrollAreaWidgetContents);

    verticalLayout_6->addWidget(scrollArea);

    retranslateUi();
}

void TabPerlinNoise::retranslateUi() {
    tile->setText(ViewsUtils::local("algoPerlinNoiseName"));
    sizeLabel->setText(ViewsUtils::local("labelSize"));
    sizeComboBox->setItemText(0, ViewsUtils::local("size100"));
    sizeComboBox->setItemText(1, ViewsUtils::local("size500"));
    sizeComboBox->setItemText(2, ViewsUtils::local("size1000"));
    sizeComboBox->setItemText(3, ViewsUtils::local("size2500"));
    sizeComboBox->setItemText(4, ViewsUtils::local("size5000"));

    seedInput->retranslateUi();
    cellSizeInput->retranslateUi();
    octavesInput->retranslateUi();
    persistenceInput->retranslateUi();
}
