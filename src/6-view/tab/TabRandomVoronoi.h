#pragma once


#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include "input/InputInteger.h"
#include "Generate.h"
#include "Tab.h"


class TabRandomVoronoi : public Tab {
public:
    TabRandomVoronoi() = default;

    TabRandomVoronoi(const TabRandomVoronoi &other) = delete;

    TabRandomVoronoi(TabRandomVoronoi &&other) noexcept = delete;

    TabRandomVoronoi &operator=(const TabRandomVoronoi &other) = delete;

    TabRandomVoronoi &operator=(TabRandomVoronoi &&other) noexcept = delete;

    ~TabRandomVoronoi() = default;

    QWidget *sizeContainer;
    QVBoxLayout *sizeContainerLayout;
    QLabel *sizeLabel;
    QComboBox *sizeComboBox;

    InputInteger *seedInput;
    InputInteger *nbPointsInput;


    virtual void setupUi() override;

    virtual void retranslateUi() override;
};

class GenerateRandomVoronoi : public Generate {
public:
    GenerateRandomVoronoi(TabRandomVoronoi* tabRandomVoronoi);

    GenerateRandomVoronoi(const GenerateRandomVoronoi &other) = delete;

    GenerateRandomVoronoi(GenerateRandomVoronoi &&other) noexcept = delete;

    GenerateRandomVoronoi &operator=(const GenerateRandomVoronoi &other) = delete;

    GenerateRandomVoronoi &operator=(GenerateRandomVoronoi &&other) noexcept = delete;

    ~GenerateRandomVoronoi() = default;

    void handleGenerate() override;

private:
    TabRandomVoronoi* tabRandomVoronoi;
};