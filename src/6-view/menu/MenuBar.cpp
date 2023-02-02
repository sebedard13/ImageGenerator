#include <iostream>
#include <thread>
#include <QFileDialog>
#include <QApplication>
#include "MenuBar.h"
#include "../ViewUtils.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/SaveImage.h"
#include "../../2-services/ThreadController.h"

MenuBar::MenuBar(QWidget *parent)
        : QMenuBar(parent) {
    this->setObjectName("menuBar");
}

void MenuBar::setupUi(QMainWindow *ViewRootClass) {
    menuFile = new QMenu(this);
    menuFile->setObjectName("menuFile");
    menuFile->setToolTipsVisible(false);
    this->addAction(menuFile->menuAction());

    actionSauvegarder = new QAction(ViewRootClass);
    actionSauvegarder->setObjectName("actionSauvegarder");
    actionSauvegarder->setIconVisibleInMenu(true);
    menuFile->addAction(actionSauvegarder);


    actionCharger = new QAction(ViewRootClass);
    actionCharger->setObjectName("actionCharger");
    actionCharger->setCheckable(false);
    actionCharger->setIconVisibleInMenu(true);
//	menuFile->addAction(actionCharger);

    actionQuiter = new QAction(ViewRootClass);
    actionQuiter->setObjectName("actionQuiter");
    actionQuiter->setIconVisibleInMenu(true);
    menuFile->addAction(actionQuiter);


    QObject::connect(actionSauvegarder, &QAction::triggered, this, &MenuBar::clickSave);
    QObject::connect(actionQuiter, &QAction::triggered, &QApplication::quit);

//    menuA_propos = new QMenu(this);
//    menuA_propos->setObjectName("menuA_propos");
//    menuA_propos->setToolTipsVisible(false);
//    this->addAction(menuA_propos->menuAction());

    actionVoir = new QAction(ViewRootClass);
    actionVoir->setObjectName("actionVoir");
//	menuA_propos->addAction(actionVoir);


    menuPerformence = new QMenu(this);
    menuPerformence->setObjectName("menuPerformence");
    menuPerformence->setToolTipsVisible(false);
    this->addAction(menuPerformence->menuAction());

    menuThreadNumber = new QAction(this);
    menuThreadNumber->setObjectName("menuThreadNumber");
    //menuThreadNumber->setSeparator(true);
    menuPerformence->addAction(menuThreadNumber);

    actionsThreadNumber = new QActionGroup(this);
    actionsThreadNumber->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);
    actionsThreadNumber->setObjectName("actionsThreadNumber");


    for (unsigned int threadNumber: threadNumbers) {
        auto *current = new QAction(this);
        current->setObjectName("actionThreadNumber" + std::to_string(threadNumber));
        actionsThreadNumber->addAction(current);
        current->setCheckable(true);
        unsigned nb = threadNumber;
        std::function<void()> lambda = [nb] { ThreadController::setThreadNumber(nb); };
        QObject::connect(current, &QAction::triggered, lambda);
        current->setText(QString::fromStdString(std::to_string(nb)));
    }
    menuPerformence->addActions(actionsThreadNumber->actions());

    auto it = std::find(threadNumbers.begin(), threadNumbers.end(), std::thread::hardware_concurrency());
    int index = it - threadNumbers.begin();
    if (it == threadNumbers.end() || index - 1 < 0) {
        actionsThreadNumber->actions()[0]->trigger();
    } else {
        actionsThreadNumber->actions()[index - 1]->trigger();
    }


    retranslateUi();
}

void MenuBar::retranslateUi() {
    actionSauvegarder->setText(ViewsUtils::local("btnSave"));
    actionCharger->setText(ViewsUtils::local("btnLoad"));
    actionQuiter->setText(ViewsUtils::local("btnQuit"));
    actionVoir->setText(ViewsUtils::local("btnSeeAbout"));
    menuFile->setTitle(ViewsUtils::local("btnFile"));
//	menuA_propos->setTitle(ViewsUtils::local("btnAbout"));
    menuPerformence->setTitle(ViewsUtils::local("btnPerformance"));
    menuThreadNumber->setText(ViewsUtils::local("btnThreadNumberTitle"));

}

void MenuBar::clickSave() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                                    "/",
                                                    "Image (*.png)");

    Controller::execute(std::make_unique<SaveImage>(fileName.toStdString()));
}

const std::vector<unsigned> MenuBar::threadNumbers{1, 2, 4, 6, 8, 12, 16};

MenuBar::~MenuBar() {
    delete actionsThreadNumber;
}
