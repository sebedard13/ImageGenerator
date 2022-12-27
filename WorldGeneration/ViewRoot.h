#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ViewRoot.h"

class ViewRoot : public QMainWindow
{
    Q_OBJECT

public:
    ViewRoot(QWidget *parent = nullptr);
    ~ViewRoot();

private:
    Ui::ViewRootClass ui;
};
