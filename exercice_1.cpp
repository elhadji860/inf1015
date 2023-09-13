
/**
* programme qui prend en entree un nombre et affiche le premier nombre premier superieur ou egal.
* \file   exercice1.cpp
* \author Sarr et Diaw
* \date   17 septembre 2023
* Cr�� le 05 septembre 2023
*/


#include <iostream>

using namespace std;

bool estPremier(int nombre) {
    if (nombre == 1) {
        return false;
    }

    if (nombre == 2) {
        return true;
    }

    for (int i = 2; i < nombre; ++i) {
        if (nombre % i == 0) { 
            return false; }
    }

    return true;
}


int main()
{
    int nombreEntr� = -1;
    cout << "Entrez un nombre entier : ";
    cin >> nombreEntr�;

    while (nombreEntr� != -1) {
        int nombrePremier = nombreEntr�;
        while (!estPremier(nombrePremier)) {
            ++nombrePremier;
        }

        cout << "Le prochain nombre premier est " << nombrePremier << "." << endl;
        
        cout << "Entrez un nombre entier :";
        cin >> nombreEntr�;
    }

    return 0;
}