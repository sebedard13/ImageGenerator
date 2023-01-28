#pragma once

#include <QFrame>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWheelEvent>
#include "GraphicView.h"

class MapScreen : public QFrame {
public:
    MapScreen() = delete;

    MapScreen(const MapScreen &other) = delete;

    MapScreen(MapScreen &&other) noexcept = delete;

    MapScreen &operator=(const MapScreen &other) = delete;

    MapScreen &operator=(MapScreen &&other) noexcept = delete;

    ~MapScreen() = default;

    QVBoxLayout *verticalLayout_2;
    GraphicView *graphicsView;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_5;
    QProgressBar *progressBar;
    QLabel *label;
    std::string messageId{"tipNothing"};

    MapScreen(QWidget *parent)
            : QFrame(parent) {}

    void setupUi(QMainWindow *ViewRootClass);

    void setupMap();

    void retranslateUi();

    void changeMessage(const std::string &key);

    void changePercent(const int &value); //0 to 100

};

