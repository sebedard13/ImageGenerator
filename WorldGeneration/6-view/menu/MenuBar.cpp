#include <iostream>
#include <QFileDialog>
#include "MenuBar.h"
#include "../ViewUtils.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/SaveImage.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
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
//	menuFile->addAction(actionQuiter);


//    menuA_propos = new QMenu(this);
//    menuA_propos->setObjectName("menuA_propos");
//    menuA_propos->setToolTipsVisible(false);
//    this->addAction(menuA_propos->menuAction());

    actionVoir = new QAction(ViewRootClass);
    actionVoir->setObjectName("actionVoir");
//	menuA_propos->addAction(actionVoir);


    QObject::connect(actionSauvegarder, &QAction::triggered, this, &MenuBar::clickSave);


    retranslateUi(ViewRootClass);
}

void MenuBar::retranslateUi(QMainWindow *ViewRootClass) {
    actionSauvegarder->setText(ViewsUtils::local("btnSave"));
    actionCharger->setText(ViewsUtils::local("btnLoad"));
    actionQuiter->setText(ViewsUtils::local("btnQuit"));
    actionVoir->setText(ViewsUtils::local("btnSeeAbout"));
    menuFile->setTitle(ViewsUtils::local("btnFile"));
//	menuA_propos->setTitle(ViewsUtils::local("btnAbout"));
}

void MenuBar::clickSave() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                                    "/",
                                                    "Image (*.png)");

   Controller::execute(std::make_unique<SaveImage>(fileName.toStdString()));
}
