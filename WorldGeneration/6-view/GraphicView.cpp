#include "GraphicView.h"
#include <iostream>

GraphicView::GraphicView(QWidget* parent): QGraphicsView::QGraphicsView(parent)
{
	setObjectName("graphicsView");
	setDragMode(QGraphicsView::ScrollHandDrag);

}

void GraphicView::wheelEvent(QWheelEvent* event)
{
	auto delta = event->angleDelta();

	if (delta.ry() > 0)
	{
		if (scaleNb < 256) {
			scale(2, 2);
			scaleNb *= 2;
		}
	}
	else
	{
		if (scaleNb > 1) {
			scale(0.5, 0.5);
			scaleNb /= 2;
		}
		
	}
}