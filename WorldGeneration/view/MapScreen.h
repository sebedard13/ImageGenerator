#pragma once
#include <QFrame>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWheelEvent>


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
	std::string messageId{ "tipNothing" };

	MapScreen(QWidget* parent) : QFrame(parent) {}

	void setupUi(QMainWindow* ViewRootClass);

	void setupMap();

	void retranslateUi(QMainWindow* ViewRootClass);

	void mousePressEvent(QMouseEvent* event) override;

	void wheelEvent(QWheelEvent* event) override;

	void changeMessage(const std::string& key);

	void changePercent(const int& value); //0 to 100

	int getPercent();
};

