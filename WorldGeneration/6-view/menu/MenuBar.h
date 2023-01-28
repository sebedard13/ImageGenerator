#pragma once


#include <QMenuBar>
#include <QMainWindow>

class MenuBar : public QMenuBar {
public:
    QMenu* menuFile;
    QMenu* menuA_propos;

    QAction* actionSauvegarder;
    QAction* actionCharger;
    QAction* actionQuiter;
    QAction* actionVoir;


    explicit MenuBar(QWidget *parent);

    void setupUi(QMainWindow* ViewRootClass);

    void retranslateUi(QMainWindow* ViewRootClass);

    void clickSave();
};
