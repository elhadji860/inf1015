/**
* programme de traitement de données pour une épicerie (aliment, type, quantité, prix unitaire).
* \file   exercice1.cpp
* \author Sarr et Diaw
* \date   17 septembre 2023
* Créé le 05 septembre 2023
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NOMBRE_ELEMENT = 10;
const string CHEMIN_INVENTAIRE = "y:\\ProfileS\\DESktop\\tp1\\exercice_5\\exercice_5\\inventaire.txt";


struct Produit {
    string nom;
    string categorie;
    string quantite;
    string prix = "-1";
};


int main()
{
    Produit produits[NOMBRE_ELEMENT];
    ifstream inventaire(CHEMIN_INVENTAIRE);
    

    int compteur = 0;
    while (compteur < NOMBRE_ELEMENT) {

        string information;
        char separation = '\t';
        getline(inventaire, information, separation);

        if (information != "") {
            Produit produit;

            produit.nom = information;

            getline(inventaire, produit.categorie, separation);
            
            getline(inventaire, information, separation);
            produit.quantite = information;

            getline(inventaire, information);
            produit.prix = information;

            produits[compteur] = produit;
        }
        ++compteur;
    }

    int positionPlusCher = 0;
    double prixPlusCher = stod(produits[0].prix);
    for (int i = 0; i < NOMBRE_ELEMENT; ++i) {
        if (produits[i].prix != "-1") {
            if (stod(produits[i].prix) > prixPlusCher) {
                positionPlusCher = i;
                prixPlusCher = stod(produits[i].prix);
            }
        }
    }

    cout << produits[positionPlusCher].quantite << " " << produits[positionPlusCher].nom << "(s) (" << produits[positionPlusCher].categorie << ") a " << produits[positionPlusCher].prix << " chacun ";

    return 0;
}
