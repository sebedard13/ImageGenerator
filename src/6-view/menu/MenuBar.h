#pragma once

#include <QMenuBar>
#include <QActionGroup>
#include <QMainWindow>

class MenuBar : public QMenuBar {
public:
    QMenu *menuFile;
    QAction *actionSauvegarder;
    QAction *actionCharger;
    QAction *actionQuiter;

    QMenu *menuA_propos;
    QAction *actionVoir;


    QMenu *menuPerformence;
    QAction *menuThreadNumber;
    QActionGroup *actionsThreadNumber;
    static const std::vector<unsigned> threadNumbers;

    explicit MenuBar(QWidget *parent);

    void setupUi(QMainWindow *ViewRootClass);

    void retranslateUi();

    void clickSave();

    virtual ~MenuBar() override;
};
