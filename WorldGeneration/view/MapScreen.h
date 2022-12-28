#pragma once
#include <QFrame>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QVBoxLayout>


class MapScreen : public QFrame
{
public:
	MapScreen() = delete;
	MapScreen(const MapScreen& other) = delete;
	MapScreen(MapScreen&& other) noexcept = delete;
	MapScreen& operator=(const MapScreen& other) = delete;
	MapScreen& operator=(MapScreen&& other) noexcept = delete;
	~MapScreen() = default;

	QVBoxLayout* verticalLayout_2;
	QGraphicsView* graphicsView;
	QFrame* frame_2;
	QVBoxLayout* verticalLayout_5;
	QProgressBar* progressBar;
	QLabel* label;

	MapScreen(QWidget* parent) : QFrame(parent) {}

	void setupUi(QMainWindow* ViewRootClass);

	void retranslateUi(QMainWindow* ViewRootClass);
};

