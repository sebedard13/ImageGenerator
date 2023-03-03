#include "Tab.h"

void Tab::setupMainUi() {
    this->setObjectName("tabDiamondSquare");
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
    title = new QLabel();
    title->setObjectName("tile");
    QFont font;
    font.setPointSize(11);
    title->setFont(font);
    mainLayout->addWidget(title);

    setupUi();

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer);
    scrollArea->setWidget(scrollAreaWidgetContents);
    verticalLayout_6->addWidget(scrollArea);

    retranslateUi();
}

QVBoxLayout* Tab::generateInputLayout(QWidget *parent) {

    auto pQvBoxLayout = new QVBoxLayout(parent);
    pQvBoxLayout->setSpacing(5);
    pQvBoxLayout->setContentsMargins(11, 11, 11, 11);
    pQvBoxLayout->setObjectName("vBoxLayout");
    pQvBoxLayout->setContentsMargins(0, 0, 0, 0);
    return pQvBoxLayout;
}
