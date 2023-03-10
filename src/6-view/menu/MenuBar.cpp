#include <thread>
#include <QFileDialog>
#include <QApplication>
#include <QShortcut>
#include "MenuBar.h"
#include "../ViewUtils.h"
#include "../../5-controller/Controller.h"
#include "../../5-controller/commands/SaveImage.h"
#include "../../2-infrastructure/ThreadController.h"
#include "../../3-services/KeyBinding.h"
#include "../ViewRoot.h"

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
    const std::string &s = KeyBinding::get("btnSave");
    const QKeySequence key = QKeySequence(QString::fromStdString(s));
    actionSauvegarder->setShortcut(key);

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

    menuLang = new QMenu(this);
    menuLang->setObjectName("menuLang");
    menuLang->setToolTipsVisible(false);
    this->addAction(menuLang->menuAction());

    actionsLang = new QActionGroup(this);
    actionsLang->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);
    actionsLang->setObjectName("actionsThreadNumber");

    std::vector<std::string> langs{Localization::getAllLanguages()};
    std::cout << langs[0] << std::endl;
    for (auto l: langs) {
        auto *current = new QAction(this);
        current->setObjectName("lang" + l);
        actionsLang->addAction(current);
        current->setCheckable(true);
        std::function < void() > lambda = [l, ViewRootClass] {
            Localization::setLanguage(l);
            reinterpret_cast<ViewRoot *>(ViewRootClass)->retranslate();
        };
        QObject::connect(current, &QAction::triggered, lambda);
        current->setText(QString::fromStdString(l));
    }
    for (int i = 0; i < langs.size(); ++i) {
        if (langs[i] == Localization::getLanguage()) {
            actionsLang->actions()[i]->trigger();
        }
    }
    menuLang->addActions(actionsLang->actions());


    retranslateUi();
}

void MenuBar::retranslateUi() {
    actionSauvegarder->setText(ViewsUtils::local("btnSave"));
    actionCharger->setText(ViewsUtils::local("btnLoad"));
    actionQuiter->setText(ViewsUtils::local("btnQuit"));
    menuFile->setTitle(ViewsUtils::local("btnFile"));
    menuPerformence->setTitle(ViewsUtils::local("btnPerformance"));
    menuThreadNumber->setText(ViewsUtils::local("btnThreadNumberTitle"));
    menuLang->setTitle(ViewsUtils::local("btnLanguages"));

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
