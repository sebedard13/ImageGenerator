#include "TabPlatec.h"

#include "../../4-domain/algos/platec/Platec.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/DoAlgo.h"
#include "../ViewUtils.h"

void TabPlatec::setupUi() {
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

    seedInput = new InputInteger("labelSeed", 0, 0);
    mainLayout->addWidget(seedInput);

    nbPlatesInput = new InputInteger("labelNbPlates", 10, 0);
    mainLayout->addWidget(nbPlatesInput);

    maxIterationInput = new InputInteger("labelMaxIteration", 570, 0);
    mainLayout->addWidget(maxIterationInput);

    maxCycleInput = new InputInteger("labelMaxCycle", 2, 0);
    mainLayout->addWidget(maxCycleInput);

    mapRoughness = new InputDouble("labelMapRoughness", 0.5);
    mainLayout->addWidget(mapRoughness);

    seaLevelInput = new InputDouble("labelSeaLevel", 0.65);
    mainLayout->addWidget(seaLevelInput);

    erosionPeriodInput = new InputInteger("labelErosionPeriod", 60, 0);
    mainLayout->addWidget(erosionPeriodInput);

    foldingRatio = new InputDouble("labelFoldingRatio", 0.001);
    mainLayout->addWidget(foldingRatio);

    aggrRatioAbs = new InputInteger("labelAggrRatioAbs", 5000, 1);
    mainLayout->addWidget(aggrRatioAbs);

    aggrRatioRel = new InputDouble("labelAggrRatioRel", 0.1);
    mainLayout->addWidget(aggrRatioRel);
}

void TabPlatec::retranslateUi() {
    title->setText(ViewsUtils::local("algoPlatecName"));
    sizeLabel->setText(ViewsUtils::local("labelSize"));
    sizeComboBox->setItemText(0, "256x256");
    sizeComboBox->setItemText(1, "512x512");
    sizeComboBox->setItemText(2, "1024x1024");
    sizeComboBox->setItemText(3, "2048x2048");
    sizeComboBox->setItemText(4, "4096x4096");

    seedInput->retranslateUi();
    nbPlatesInput->retranslateUi();
    maxIterationInput->retranslateUi();
    maxCycleInput->retranslateUi();
    mapRoughness->retranslateUi();
    seaLevelInput->retranslateUi();
    erosionPeriodInput->retranslateUi();
    foldingRatio->retranslateUi();
    aggrRatioAbs->retranslateUi();
    aggrRatioRel->retranslateUi();
}

GeneratePlatec::GeneratePlatec(TabPlatec *tabPlatec)
        : tabPlatec(tabPlatec) {

}

void GeneratePlatec::handleGenerate() {
    constexpr int sizes[5]{256, 512, 1024, 2048, 4096};
    const int sizeIndex = tabPlatec->sizeComboBox->currentIndex();

    auto algo = std::make_unique<Platec>(sizes[sizeIndex],
            tabPlatec->seaLevelInput->getValue(),
            tabPlatec->erosionPeriodInput->getValue(),
            tabPlatec->foldingRatio->getValue(),
            tabPlatec->aggrRatioAbs->getValue(),
            tabPlatec->aggrRatioRel->getValue(),
            tabPlatec->nbPlatesInput->getValue(),
            tabPlatec->maxCycleInput->getValue(),
            tabPlatec->maxIterationInput->getValue(),
            tabPlatec->mapRoughness->getValue(),
            tabPlatec->seedInput->getValue()
    );

    Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}



