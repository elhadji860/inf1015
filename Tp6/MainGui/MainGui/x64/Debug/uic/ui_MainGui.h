/********************************************************************************
** Form generated from reading UI file 'MainGui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGUI_H
#define UI_MAINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGuiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainGuiClass)
    {
        if (MainGuiClass->objectName().isEmpty())
            MainGuiClass->setObjectName(QString::fromUtf8("MainGuiClass"));
        MainGuiClass->resize(600, 400);
        menuBar = new QMenuBar(MainGuiClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MainGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainGuiClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainGuiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MainGuiClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainGuiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainGuiClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainGuiClass->setStatusBar(statusBar);

        retranslateUi(MainGuiClass);

        QMetaObject::connectSlotsByName(MainGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainGuiClass)
    {
        MainGuiClass->setWindowTitle(QCoreApplication::translate("MainGuiClass", "MainGui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGuiClass: public Ui_MainGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGUI_H
