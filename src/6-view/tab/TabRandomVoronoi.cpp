
#include "TabRandomVoronoi.h"
#include "../ViewUtils.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/DoAlgo.h"
#include "../../4-domain/algos/RandomVoronoi.h"

void TabRandomVoronoi::setupUi() {
    sizeContainer = new QWidget();
    sizeContainer->setObjectName("sizeContainer");
    sizeContainerLayout = generateInputLayout(sizeContainer);
    sizeLabel = new QLabel(sizeContainer);
    sizeLabel->setObjectName("sizeLabel");
    sizeContainerLayout->addWidget(sizeLabel);
    sizeComboBox = new QComboBox(sizeContainer);
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

    nbPointsInput = new InputInteger("labelNbPoints", 5, 2, 500);
    mainLayout->addWidget(nbPointsInput );
}

void TabRandomVoronoi::retranslateUi() {
    title->setText(ViewsUtils::local("algoRandomVoronoiName"));
    sizeLabel->setText(ViewsUtils::local("labelSize"));
    sizeComboBox->setItemText(0, ViewsUtils::local("size100"));
    sizeComboBox->setItemText(1, ViewsUtils::local("size500"));
    sizeComboBox->setItemText(2, ViewsUtils::local("size1000"));
    sizeComboBox->setItemText(3, ViewsUtils::local("size2500"));
    sizeComboBox->setItemText(4, ViewsUtils::local("size5000"));

    seedInput->retranslateUi();
}

GenerateRandomVoronoi::GenerateRandomVoronoi(TabRandomVoronoi *tabRandomVoronoi)
        : tabRandomVoronoi(tabRandomVoronoi)
{}

void GenerateRandomVoronoi::handleGenerate() {
    constexpr int sizes[5]{100, 500, 1000, 2500, 5000};
    const int sizeIndex = tabRandomVoronoi->sizeComboBox->currentIndex();

    auto algo = std::make_unique<RandomVoronoi>(tabRandomVoronoi->nbPointsInput->getValue(),sizes[sizeIndex], sizes[sizeIndex],
                                                tabRandomVoronoi->seedInput->getValue()
    );

    Controller::execute(std::make_unique<DoAlgo>(std::move(algo)));
}
