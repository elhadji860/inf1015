/********************************************************************************
** Form generated from reading UI file 'TP6_inf1015.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TP6_INF1015_H
#define UI_TP6_INF1015_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TP6_inf1015Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TP6_inf1015Class)
    {
        if (TP6_inf1015Class->objectName().isEmpty())
            TP6_inf1015Class->setObjectName("TP6_inf1015Class");
        TP6_inf1015Class->resize(600, 400);
        menuBar = new QMenuBar(TP6_inf1015Class);
        menuBar->setObjectName("menuBar");
        TP6_inf1015Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TP6_inf1015Class);
        mainToolBar->setObjectName("mainToolBar");
        TP6_inf1015Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(TP6_inf1015Class);
        centralWidget->setObjectName("centralWidget");
        TP6_inf1015Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TP6_inf1015Class);
        statusBar->setObjectName("statusBar");
        TP6_inf1015Class->setStatusBar(statusBar);

        retranslateUi(TP6_inf1015Class);

        QMetaObject::connectSlotsByName(TP6_inf1015Class);
    } // setupUi

    void retranslateUi(QMainWindow *TP6_inf1015Class)
    {
        TP6_inf1015Class->setWindowTitle(QCoreApplication::translate("TP6_inf1015Class", "TP6_inf1015", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TP6_inf1015Class: public Ui_TP6_inf1015Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TP6_INF1015_H
