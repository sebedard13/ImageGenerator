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
#include "input/InputDouble.h"

class TabPlatec : public Tab {
public:
    TabPlatec() = default;

    TabPlatec(const TabPlatec &other) = delete;

    TabPlatec(TabPlatec &&other) noexcept = delete;

    TabPlatec &operator=(const TabPlatec &other) = delete;

    TabPlatec &operator=(TabPlatec &&other) noexcept = delete;

    ~TabPlatec() = default;

    QWidget *sizeContainer;
    QVBoxLayout *sizeContainerLayout;
    QLabel *sizeLabel;
    QComboBox *sizeComboBox;

    InputInteger *seedInput;
    InputInteger *nbPlatesInput;
    InputInteger *maxIterationInput;// def=570
    InputInteger *maxCycleInput; // 0-1 | def=2
    InputDouble *mapRoughness; // 0-4 | def=0.5 |
    InputDouble *seaLevelInput; // 0-1 | def=0.65 | start sea level
    InputInteger *erosionPeriodInput; // 0- | def=60 | 0 to not have erosion
    InputDouble *foldingRatio; // 0-1 | def=0.001 | percent of height lost from continental collision
    InputInteger *aggrRatioAbs; // 1- | def=5000 | nb of pixel of two plates colliding to merge them
    InputDouble *aggrRatioRel; // 0-1 | def=0.1 | % of smaller plate of two plates colliding to merge them


    virtual void setupUi() override;

    virtual void retranslateUi() override;

private:
};

class GeneratePlatec : public Generate {
public:
    GeneratePlatec(TabPlatec *tabPlatec);

    GeneratePlatec(const GeneratePlatec &other) = delete;

    GeneratePlatec(GeneratePlatec &&other) noexcept = delete;

    GeneratePlatec &operator=(const GeneratePlatec &other) = delete;

    GeneratePlatec &operator=(GeneratePlatec &&other) noexcept = delete;

    ~GeneratePlatec() = default;

    void handleGenerate() override;

private:
    TabPlatec *tabPlatec;
};