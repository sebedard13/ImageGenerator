
#include "TabRandomVoronoi.h"
#include "../ViewUtils.h"

void TabRandomVoronoi::setupUi(QMainWindow *ViewRootClass) {
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

    nbPointsInput = new InputInteger("labelNbPoints", 5, 2, 500);
    mainLayout->addWidget(nbPointsInput );


    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);mainLayout->addItem(verticalSpacer);

    scrollArea->setWidget(scrollAreaWidgetContents);

    verticalLayout_6->addWidget(scrollArea);

    retranslateUi();

}

void TabRandomVoronoi::retranslateUi() {
    tile->setText(ViewsUtils::local("algoRandomVoronoiName"));
    sizeLabel->setText(ViewsUtils::local("labelSize"));
    sizeComboBox->setItemText(0, ViewsUtils::local("size100"));
    sizeComboBox->setItemText(1, ViewsUtils::local("size500"));
    sizeComboBox->setItemText(2, ViewsUtils::local("size1000"));
    sizeComboBox->setItemText(3, ViewsUtils::local("size2500"));
    sizeComboBox->setItemText(4, ViewsUtils::local("size5000"));

    seedInput->retranslateUi();
}
