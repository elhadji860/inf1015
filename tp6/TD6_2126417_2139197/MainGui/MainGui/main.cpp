/**
* Programme qui permet une representation graphique d'une caisse enregistreuse.
* \file   main.cpp
* \author Sarr et Diaw
* \date   03 decembre 2023
* Créé le 21 Novembre 2023
*/

#include "MainGui.h"
#include <QtWidgets/QApplication>
#include "Caisse.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGui w;
    w.show();
    return a.exec();
}
