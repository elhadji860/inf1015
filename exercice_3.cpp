/**
*  programme qui détermine si une collision se produit dans les x premières secondes d’un trajet.
* \file   exercice1.cpp
* \author Sarr et Diaw
* \date   17 septembre 2023
* Créé le 05 septembre 2023
*/

#include <iostream>

using namespace std;

bool estDansIntervalle(int nombre, int borne1, int borne2) {
    if (!(nombre <= borne2 && nombre >= borne1)) {
        return false;
    }
    return true;
}

int main()
{
    int positionTrain1 = 0;
    int positionTrain2 = 0;
    int vitesseTrain1 = 0;
    int vitesseTrain2 = 0;
    int nombreSeconde = 1;
    int tempsTotal = 0;

    cout << "Entrez le temps total : ";
    cin >> tempsTotal;

    cout << "Entrez la position initiale du premier train : ";
    cin >> positionTrain1;

    cout << "Entrez la vitesse du premier train : ";
    cin >> vitesseTrain1;

    cout << "Entrez la position initiale du second train : ";
    cin >> positionTrain2;

    cout << "Entrez la vitesse du second train : ";
    cin >> vitesseTrain2;

    //partie necessaire dans le cas ou le train1 est place apres le train 2
    int vraiPosition1 = positionTrain1;
    int vraiPosition2 = positionTrain2;
    int vraiVitesse1 = vitesseTrain1;
    int vraiVitesse2 = vitesseTrain2;

    if (positionTrain1 > positionTrain2) {
        int temp;
        temp = positionTrain1;
        positionTrain1 = positionTrain2;
        positionTrain2 = temp;

        temp = vitesseTrain1;
        vitesseTrain1 = vitesseTrain2;
        vitesseTrain2 = temp;
    }

   
    bool estFini = !(tempsTotal == 0 || (estDansIntervalle(positionTrain2, -INFINITY, positionTrain1)));
    while (estFini) {
        cout << "Apres " << nombreSeconde << " seconde(s)" << endl;
        cout << "Train 1 : " << vraiPosition1 << endl;
        cout << "Train 2 : " << vraiPosition2 << endl;
        
        vraiPosition1 += vraiVitesse1;
        vraiPosition2 += vraiVitesse2;
        positionTrain1 += vitesseTrain1;
        positionTrain2 += vitesseTrain2;
        ++nombreSeconde;
        --tempsTotal;
    }

    cout << "Apres " << nombreSeconde << " seconde(s)" << endl;
    cout << "Train 1 : " << vraiPosition1 << endl;
    cout << "Train 2 : " << vraiPosition2 << endl;


    if (estDansIntervalle(positionTrain2, -INFINITY, positionTrain1)) {
        cout << "Il y a eu une collision pendant la " << nombreSeconde << "e seconde!" << endl;
    }
    else {
        cout << "Il n'y a pas eu de collision ";
    }

    return 0;
}