#include "TabPerlinNoise.h"

#include <iostream>

#include "../ViewUtils.h"

void TabPerlinNoise::setupUi(QMainWindow* ViewRootClass)
{
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
	verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents);
	verticalLayout_7->setSpacing(10);
	verticalLayout_7->setContentsMargins(11, 11, 11, 11);
	verticalLayout_7->setObjectName("verticalLayout_7");
	verticalLayout_7->setContentsMargins(9, -1, -1, -1);
	label_18 = new QLabel(scrollAreaWidgetContents);
	label_18->setObjectName("label_18");
	QFont font;
	font.setPointSize(11);
	label_18->setFont(font);

	verticalLayout_7->addWidget(label_18);

	widget = new QWidget(scrollAreaWidgetContents);
	widget->setObjectName("widget");
	verticalLayout_9 = new QVBoxLayout(widget);
	verticalLayout_9->setSpacing(5);
	verticalLayout_9->setContentsMargins(11, 11, 11, 11);
	verticalLayout_9->setObjectName("verticalLayout_9");
	verticalLayout_9->setContentsMargins(0, 0, 0, 0);
	label_2 = new QLabel(widget);
	label_2->setObjectName("label_2");

	verticalLayout_9->addWidget(label_2);

	comboBox = new QComboBox(widget);
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->setObjectName("comboBox");

	verticalLayout_9->addWidget(comboBox);

	verticalLayout_7->addWidget(widget);

	label_5 = new QLabel(scrollAreaWidgetContents);
	label_5->setObjectName("label_5");

	verticalLayout_7->addWidget(label_5);

	label_6 = new QLabel(scrollAreaWidgetContents);
	label_6->setObjectName("label_6");

	verticalLayout_7->addWidget(label_6);

	label_7 = new QLabel(scrollAreaWidgetContents);
	label_7->setObjectName("label_7");

	verticalLayout_7->addWidget(label_7);

	label_8 = new QLabel(scrollAreaWidgetContents);
	label_8->setObjectName("label_8");

	verticalLayout_7->addWidget(label_8);

	label_9 = new QLabel(scrollAreaWidgetContents);
	label_9->setObjectName("label_9");

	verticalLayout_7->addWidget(label_9);

	label_10 = new QLabel(scrollAreaWidgetContents);
	label_10->setObjectName("label_10");

	verticalLayout_7->addWidget(label_10);

	label_11 = new QLabel(scrollAreaWidgetContents);
	label_11->setObjectName("label_11");

	verticalLayout_7->addWidget(label_11);

	label_12 = new QLabel(scrollAreaWidgetContents);
	label_12->setObjectName("label_12");

	verticalLayout_7->addWidget(label_12);

	label_13 = new QLabel(scrollAreaWidgetContents);
	label_13->setObjectName("label_13");

	verticalLayout_7->addWidget(label_13);

	label_14 = new QLabel(scrollAreaWidgetContents);
	label_14->setObjectName("label_14");

	verticalLayout_7->addWidget(label_14);

	label_15 = new QLabel(scrollAreaWidgetContents);
	label_15->setObjectName("label_15");

	verticalLayout_7->addWidget(label_15);

	label_16 = new QLabel(scrollAreaWidgetContents);
	label_16->setObjectName("label_16");

	verticalLayout_7->addWidget(label_16);

	label_17 = new QLabel(scrollAreaWidgetContents);
	label_17->setObjectName("label_17");

	verticalLayout_7->addWidget(label_17);

	verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	verticalLayout_7->addItem(verticalSpacer);

	scrollArea->setWidget(scrollAreaWidgetContents);

	verticalLayout_6->addWidget(scrollArea);

	retranslateUi(ViewRootClass);
}

void TabPerlinNoise::retranslateUi(QMainWindow* ViewRootClass)
{
	label_18->setText(ViewsUtils::local("algo1Name"));
	label_2->setText(ViewsUtils::local("emptytext"));
	comboBox->setItemText(0, ViewsUtils::local("worldSize1"));
	comboBox->setItemText(1, ViewsUtils::local("worldSize2"));

	label_5->setText(ViewsUtils::local("emptytext"));
	label_6->setText(ViewsUtils::local("emptytext"));
	label_7->setText(ViewsUtils::local("emptytext"));
	label_8->setText(ViewsUtils::local("emptytext"));
	label_9->setText(ViewsUtils::local("emptytext"));
	label_10->setText(ViewsUtils::local("emptytext"));
	label_11->setText(ViewsUtils::local("emptytext"));
	label_12->setText(ViewsUtils::local("emptytext"));
	label_13->setText(ViewsUtils::local("emptytext"));
	label_14->setText(ViewsUtils::local("emptytext"));
	label_15->setText(ViewsUtils::local("emptytext"));
	label_16->setText(ViewsUtils::local("emptytext"));
	label_17->setText(ViewsUtils::local("emptytext"));
}
