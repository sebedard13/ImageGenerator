#pragma once

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <utility>
#include <qwidget.h>
#include <QPushButton>
#include "../../../2-infrastructure/RandomEngine.h"

class InputSeed :
        public QWidget {
public:

    InputSeed() {
        setupUi();
    }


    void setupUi();

    void retranslateUi();

    void changeInput();

    void generateRandom();

    [[nodiscard]] unsigned getValue() const { return value; }

private:
    QVBoxLayout* containerLayout;
    QLabel* label;
    QLineEdit* input;
    QPushButton* randomBtn;

    void setValue(unsigned v);

    const std::string textID = "labelSeed";
    const unsigned min = 0;
    const unsigned max = UINT32_MAX;
    unsigned value;
    RandomEngine randomEngine{static_cast<unsigned int>(std::time(nullptr))};

};

