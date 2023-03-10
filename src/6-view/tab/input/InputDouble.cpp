#include "InputDouble.h"


#include "../../ViewUtils.h"

void InputDouble::setupUi() {
    containerLayout = new QVBoxLayout(this);
    containerLayout->setSpacing(5);
    containerLayout->setContentsMargins(11, 11, 11, 11);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);
    containerLayout->addWidget(label);
    label->setWordWrap(true);
    input = new QLineEdit(this);
    setValue(defaultV);
    containerLayout->addWidget(input);
    retranslateUi();

    connect(input, &QLineEdit::editingFinished, this, &InputDouble::changeInput);
}

void InputDouble::retranslateUi() {
    label->setText(ViewsUtils::local(textID));
}

void InputDouble::changeInput() {
    QString string = input->text();
    bool validConversion;
    const double numberDouble = string.toDouble(&validConversion);
    if (!validConversion) {
        setValue(defaultV);
    } else {
        if (numberDouble > max) {
            setValue(max);
        } else if (numberDouble < min) {
            setValue(min);
        } else {
            setValue(numberDouble);
        }
    }
}

void InputDouble::setValue(const double v) {
    value = v;
    input->setText(QString::number(v));
}
