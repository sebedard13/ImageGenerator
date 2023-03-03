#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

class Tab : public QWidget {

public:
    void setupMainUi();

    virtual void retranslateUi() = 0;

private:
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSpacerItem *verticalSpacer;
    virtual void setupUi() = 0;
protected:


    QLabel *title;
    QVBoxLayout *mainLayout;

    static QVBoxLayout *generateInputLayout(QWidget *parent);
};