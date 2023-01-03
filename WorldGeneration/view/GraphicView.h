#pragma once
#include <qgraphicsview.h>
#include <QWheelEvent>

class GraphicView : public QGraphicsView
{
private:
	unsigned int scaleNb = 2;
public:  
	GraphicView(QWidget*parent);

	void wheelEvent(QWheelEvent* event) override;
};

