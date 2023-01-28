#include "InputInteger.h"

#include <iostream>

#include "../../ViewUtils.h"

void InputInteger::setupUi() {
    containerLayout = new QVBoxLayout(this);
    containerLayout->setSpacing(5);
    containerLayout->setContentsMargins(11, 11, 11, 11);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);
    containerLayout->addWidget(label);
    input = new QLineEdit(this);
    setValue(defaultV);
    containerLayout->addWidget(input);
    retranslateUi();

    connect(input, &QLineEdit::editingFinished, this, &InputInteger::changeInput);
}

void InputInteger::retranslateUi() {
    label->setText(ViewsUtils::local(textID));
}

void InputInteger::changeInput() {
    QString string = input->text();
    bool validConversion;
    const long numberLong = string.toLong(&validConversion);
    if (!validConversion) {
        setValue(defaultV);

    } else {
        if (numberLong > max) {
            setValue(max);
        } else if (numberLong < min) {
            setValue(min);
        } else {
            setValue(static_cast<int>(numberLong));
        }
    }
}

void InputInteger::setValue(const int v) {
    value = v;
    input->setText(QString::number(v));
}
