#include "MapScreen.h"

#include <iostream>

#include "ViewUtils.h"

void MapScreen::setupUi(QMainWindow* ViewRootClass)
{
	this->setObjectName("this");
	verticalLayout_2 = new QVBoxLayout(this);
	verticalLayout_2->setSpacing(6);
	verticalLayout_2->setContentsMargins(11, 11, 11, 11);
	verticalLayout_2->setObjectName("verticalLayout_2");
	verticalLayout_2->setContentsMargins(0, 0, 0, 0);
	graphicsView = new QGraphicsView(this);
	graphicsView->setObjectName("graphicsView");

	verticalLayout_2->addWidget(graphicsView);

	frame_2 = new QFrame(this);
	frame_2->setObjectName("frame_2");
	frame_2->setAutoFillBackground(true);
	frame_2->setFrameShape(QFrame::StyledPanel);
	frame_2->setFrameShadow(QFrame::Plain);
	verticalLayout_5 = new QVBoxLayout(frame_2);
	verticalLayout_5->setSpacing(1);
	verticalLayout_5->setContentsMargins(11, 11, 11, 11);
	verticalLayout_5->setObjectName("verticalLayout_5");
	verticalLayout_5->setContentsMargins(5, 5, 5, 5);
	progressBar = new QProgressBar(frame_2);
	progressBar->setObjectName("progressBar");
	QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
	progressBar->setSizePolicy(sizePolicy3);
	QFont font1;
	font1.setPointSize(9);
	progressBar->setFont(font1);
	progressBar->setValue(0);

	verticalLayout_5->addWidget(progressBar);

	label = new QLabel(frame_2);
	label->setObjectName("label");
	QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
	sizePolicy4.setHorizontalStretch(0);
	sizePolicy4.setVerticalStretch(0);
	sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(sizePolicy4);

	verticalLayout_5->addWidget(label);
	verticalLayout_2->addWidget(frame_2);

	retranslateUi(ViewRootClass);

	setupMap();
}

void MapScreen::setupMap()
{
	const int squareSize = 5;
	const int tileSize = 100;

	QGraphicsScene* scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	QPen pen = QPen(QColor(Qt::black));
	QBrush brush = QBrush(QColor(Qt::blue));
	scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
	for (int i = 0; i < tileSize; ++i)
	{
		std::cout << i * tileSize << "/" << tileSize * tileSize << "\r";
		for (int j = 0; j < tileSize; ++j)
		{
			scene->addRect(i * squareSize, j * squareSize, squareSize, squareSize, pen, brush);
		}
	}
	std::cout << tileSize * tileSize << "/" << tileSize * tileSize << std::endl;


	graphicsView->setScene(scene);
	graphicsView->show();
}

void MapScreen::retranslateUi(QMainWindow* ViewRootClass)
{
	label->setText(ViewsUtils::local("tipNothing"));
}

void MapScreen::mousePressEvent(QMouseEvent* event)
{
	QFrame::mousePressEvent(event);
	graphicsView->rotate(15);
}

void MapScreen::wheelEvent(QWheelEvent* event)
{
	//QFrame::wheelEvent(event);
	auto delta = event->angleDelta();

	std::cout << delta.rx() << std::endl;
	std::cout << delta.ry() << std::endl;
	std::cout << delta.x() << std::endl;
	std::cout << delta.y() << std::endl;

	if (delta.ry() > 0)
	{
		graphicsView->scale(2, 2);
	}
	else
	{
		graphicsView->scale(0.5, 0.5);
	}
}
