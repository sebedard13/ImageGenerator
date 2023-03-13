#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include "Generate.h"
#include "input/InputInteger.h"
#include "input/InputDouble.h"
#include "Tab.h"
#include "input/InputSeed.h"


class TabDiamondSquare;

class GenerateDiamondSquare : public Generate {
public:
    GenerateDiamondSquare() = delete;

    GenerateDiamondSquare(const GenerateDiamondSquare& other) = delete;

    GenerateDiamondSquare(GenerateDiamondSquare&& other) noexcept = delete;

    GenerateDiamondSquare& operator=(const GenerateDiamondSquare& other) = delete;

    GenerateDiamondSquare& operator=(GenerateDiamondSquare&& other) noexcept = delete;

    ~GenerateDiamondSquare() = default;

    void handleGenerate() override;

    GenerateDiamondSquare(TabDiamondSquare* tabDiamondSquare);

private:
    TabDiamondSquare* tabDiamondSquare;
};


class TabDiamondSquare : public Tab {
public:
    TabDiamondSquare() = default;

    TabDiamondSquare(const TabDiamondSquare& other) = delete;

    TabDiamondSquare(TabDiamondSquare&& other) noexcept = delete;

    TabDiamondSquare& operator=(const TabDiamondSquare& other) = delete;

    TabDiamondSquare& operator=(TabDiamondSquare&& other) noexcept = delete;

    QWidget* sizeContainer;
    QVBoxLayout* sizeContainerLayout;
    QLabel* sizeLabel;
    QComboBox* sizeComboBox;

    InputDouble* persistenceInput;
    InputSeed* seedInput;


    virtual void setupUi() override;

    virtual void retranslateUi() override;
};