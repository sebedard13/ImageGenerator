#pragma once

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "input/InputDouble.h"
#include "input/InputInteger.h"

#include "Generate.h"
#include "Tab.h"
#include "input/InputSeed.h"

class TabPerlinNoise : public Tab {
public:
    TabPerlinNoise() = default;

    TabPerlinNoise(const TabPerlinNoise& other) = delete;

    TabPerlinNoise(TabPerlinNoise&& other) noexcept = delete;

    TabPerlinNoise& operator=(const TabPerlinNoise& other) = delete;

    TabPerlinNoise& operator=(TabPerlinNoise&& other) noexcept = delete;

    QWidget* sizeContainer;
    QVBoxLayout* sizeContainerLayout;
    QLabel* sizeLabel;
    QComboBox* sizeComboBox;

    InputInteger* cellSizeInput;
    InputInteger* octavesInput;
    InputDouble* persistenceInput;
    InputSeed* seedInput;

    virtual void setupUi() override;

    virtual void retranslateUi() override;
};

class GeneratePerlinNoise : public Generate {
public:
    explicit GeneratePerlinNoise(TabPerlinNoise* tab_perlin_noise)
            : tabPerlinNoise(tab_perlin_noise) {}

    GeneratePerlinNoise(const GeneratePerlinNoise& other) = delete;

    GeneratePerlinNoise(GeneratePerlinNoise&& other) noexcept = delete;

    GeneratePerlinNoise& operator=(const GeneratePerlinNoise& other) = delete;

    GeneratePerlinNoise& operator=(GeneratePerlinNoise&& other) noexcept = delete;

    ~GeneratePerlinNoise() = default;

    void handleGenerate() final;

private:
    TabPerlinNoise* tabPerlinNoise;
};
