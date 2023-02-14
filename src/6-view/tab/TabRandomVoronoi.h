#pragma once


#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include "input/InputInteger.h"

class TabRandomVoronoi : public QWidget {
public:
    TabRandomVoronoi() = default;

    TabRandomVoronoi(const TabRandomVoronoi &other) = delete;

    TabRandomVoronoi(TabRandomVoronoi &&other) noexcept = delete;

    TabRandomVoronoi &operator=(const TabRandomVoronoi &other) = delete;

    TabRandomVoronoi &operator=(TabRandomVoronoi &&other) noexcept = delete;

    ~TabRandomVoronoi() = default;

    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *mainLayout;
    QLabel *tile;

    QWidget *sizeContainer;
    QVBoxLayout *sizeContainerLayout;
    QLabel *sizeLabel;
    QComboBox *sizeComboBox;

    InputInteger *seedInput;
    InputInteger *nbPointsInput;

    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *ViewRootClass);

    void retranslateUi();


};
