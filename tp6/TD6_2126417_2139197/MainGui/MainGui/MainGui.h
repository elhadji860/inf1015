#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainGui.h"
#include "Caisse.h"
#include "qlayout.h"
#include <QHBoxLayout>
#include <qlabel.h>
#include "qlineedit.h"
#include <QVBoxLayout>
#include "qwidget.h"
#include "qpushbutton.h"
#include <iostream>
#include "qcheckbox.h"
#include "qlistwidget.h"
#include "qvariant.h"


class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    MainGui(QWidget *parent = nullptr);
    MainGui(Caisse* Caisse, QWidget* parent = nullptr);
    ~MainGui();
public slots:
    void controlAjouterArticle();
    void controlRetirerArticle();
    void ajouterListWidgetItem();
    void retireListWidgetITem();
    void controlReinitialiser();
    void update();
    void reset();

private:
    //attributs:
    Ui::MainGuiClass ui;
    Caisse* caisse_;
    bool caisseIsLocal_ = false;
    QLineEdit* descriptionLineEdit_;
    QLineEdit* prixLineEdit_;
    QPushButton* ajouter_;
    QPushButton* retirer_;
    QPushButton* reinitialiser_;
    QCheckBox* taxableOption_;
    QListWidget* affichage_;
    QLabel* totalAvantTaxes_;
    QLabel* totalDesTaxes_;
    QLabel* totalAPayer_;

    //fonctions:
    void setUp();
    void setUi();
    //comme cette partie n'etait pas obligatoire on a juste copier le programme du prof
    void setMenu();
    

};
