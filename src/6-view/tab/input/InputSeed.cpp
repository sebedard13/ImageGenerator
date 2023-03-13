#include "InputSeed.h"

#include <iostream>

#include "../../ViewUtils.h"

void InputSeed::setupUi() {
    containerLayout = new QVBoxLayout(this);
    containerLayout->setSpacing(5);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);

    label->setWordWrap(true);
    input = new QLineEdit(this);
    randomBtn = new QPushButton(this);
    randomBtn->setIcon(QIcon("icons/redoRandom.png"));
    randomBtn->setFixedSize(20, 20);
    QWidget * window = new QWidget;
    auto h = new QHBoxLayout(window);
    h->setContentsMargins(0, 0, 0, 0);

    setValue(randomEngine.range(min, max));
    containerLayout->addWidget(label);
    h->addWidget(input);
    h->addWidget(randomBtn);
    containerLayout->addWidget(window);
    retranslateUi();

    connect(input, &QLineEdit::editingFinished, this, &InputSeed::changeInput);

    connect(randomBtn, &QPushButton::clicked, this, &InputSeed::generateRandom);
}

void InputSeed::retranslateUi() {
    label->setText(ViewsUtils::local(textID));
}

void InputSeed::changeInput() {
    QString string = input->text();
    bool validConversion;
    const unsigned long numberLong = string.toLong(&validConversion);
    if (!validConversion) {
        setValue(randomEngine.range(min, max));

    } else {
        if (numberLong > max) {
            setValue(max);
        }
            //always false
            /*else if (numberLong < min) {
                setValue(min);
            }*/
        else {
            setValue(static_cast<unsigned>(numberLong));
        }
    }
}

void InputSeed::setValue(const unsigned v) {
    value = v;
    input->setText(QString::number(v));
}

void InputSeed::generateRandom() {
    setValue(randomEngine.range(min, max));
}
