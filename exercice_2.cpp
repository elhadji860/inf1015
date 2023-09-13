/**
* programme qui permet de deviner la valeur d’un nombre entier choisi aléatoirement entre 0 et 1000.
* \file   exercice1.cpp
* \author Sarr et Diaw
* \date   17 septembre 2023
* Créé le 05 septembre 2023
*/


#include<iostream>
#include<cstdlib>

using namespace std;

const int BORNE_SUPERIEUR = 1000;
const int BORNE_INFERIEUR = 0;


bool estDansIntervalle(int nombre, int borne1, int borne2) {

    if (!(nombre <= borne2 && nombre >= borne1)) {
        return false;
    }

    return true;
}

int main() {
    //pour l'utilisation de la fonction rand (information trouvee sur stackovrflow)
    srand((unsigned)time(NULL));

    int choix=0;
    cout << "Entrez un nombre entier :";
    cin >> choix;

    while (!estDansIntervalle(choix,BORNE_INFERIEUR, BORNE_SUPERIEUR)) {
        cout << "Entrez un nombre entier :";
        cin >> choix;
    }

    int compteur{ 0 };
    int x;
    x = rand() % 1000;

    while (x != choix) {
        if (x > choix) {
            cout << "trop petit" << endl;
        }

        if (x < choix) {
            cout << "trop grand" << endl;
        }

        cout << "Entrez un nombre entier :";
        cin >> choix;
        
        ++compteur;

    }
    cout << "Bravo! Vous avez reussi en " << compteur << " tentatives.";

    return 0;
}