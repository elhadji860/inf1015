/**
* programme qui saisit un tableau d’entiers (pas de vérification nécessaire) de taille 10 et le trie.
* \file   exercice1.cpp
* \author Sarr et Diaw
* \date   17 septembre 2023
* Créé le 05 septembre 2023
*/

#include <iostream>

using namespace std;

const int NOMBRE_ENTIERS = 10;

int main()
{
    int entiers[NOMBRE_ENTIERS];
    cout << "entrez 10 entiers : ";
    int compteur = 0;
    while (compteur < NOMBRE_ENTIERS) {
        cin >> entiers[compteur];
        ++compteur;
    }

    for (int i = 0; i < NOMBRE_ENTIERS; ++i) {
        int position = i;
        int min = entiers[i];
        for (int j = i; j < NOMBRE_ENTIERS; ++j) {
            if (entiers[j] < min) {
                min = entiers[j];
                position = j;
            }
        }

        int temp = entiers[i];
        entiers[i] = min;
        entiers[position] = temp;
    }

    cout << "Voici le tableau trié : ";
    for (int i = 0; i < NOMBRE_ENTIERS; ++i) {
        cout << entiers[i] << " ";
    }

    return 0;
}
