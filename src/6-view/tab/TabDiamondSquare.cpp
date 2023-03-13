#include "TabDiamondSquare.h"
#include "../../4-domain/algos/DiamondSquare.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/DoAlgo.h"
#include "../ViewUtils.h"

void GenerateDiamondSquare::handleGenerate() {
    constexpr int sizes[5]{257, 513, 1025, 2049, 4097};
    const int sizeIndex = tabDiamondSquare->sizeComboBox->currentIndex();


    auto algo = std::make_unique<DiamondSquare>(sizes[sizeIndex],
            tabDiamondSquare->seedInput->getValue(),
            tabDiamondSquare->persistenceInput->getValue()
    );

    Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}

GenerateDiamondSquare::GenerateDiamondSquare(TabDiamondSquare* tabDiamondSquare)
        : tabDiamondSquare(tabDiamondSquare) {}


void TabDiamondSquare::setupUi() {
    sizeContainer = new QWidget();
    sizeContainer->setObjectName("sizeContainer");
    sizeContainerLayout = generateInputLayout(sizeContainer);
    sizeLabel = new QLabel();
    sizeLabel->setObjectName("sizeLabel");
    sizeContainerLayout->addWidget(sizeLabel);
    sizeComboBox = new QComboBox();
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->addItem(QString());
    sizeComboBox->setCurrentIndex(1);
    sizeComboBox->setObjectName("sizeComboBox");
    sizeContainerLayout->addWidget(sizeComboBox);
    mainLayout->addWidget(sizeContainer);

    seedInput = new InputSeed();
    mainLayout->addWidget(seedInput);

    persistenceInput = new InputDouble("labelRoughness", 0.8, 0.1, 5);
    mainLayout->addWidget(persistenceInput);
}

void TabDiamondSquare::retranslateUi() {
    title->setText(ViewsUtils::local("algoDiamondSquareName"));
    sizeLabel->setText(ViewsUtils::local("labelSize"));
    sizeComboBox->setItemText(0, "257x257");
    sizeComboBox->setItemText(1, "513x513");
    sizeComboBox->setItemText(2, "1025x1025");
    sizeComboBox->setItemText(3, "2049x2049");
    sizeComboBox->setItemText(4, "4097x4097");

    seedInput->retranslateUi();
    persistenceInput->retranslateUi();

}
