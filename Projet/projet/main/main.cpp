/**
* jeux d'aventure 
* \file   main.cpp
* \author Sarr et Diaw
* \date   19 Decembre 2023
* Créé le 03 Decembre 2023
*/

#include <iostream>
#include "Affichage.h"


using namespace std;

int main()
{
	shared_ptr<Monde> ptrMonde = make_shared<Monde>();
	shared_ptr<Controleur> ptrControleur = make_shared<Controleur>(ptrMonde);
	Affichage  affichage(ptrMonde, ptrControleur);

	Etat etatActuel = Etat::AFFICHAGE;
	
	while (true)
	{
		switch (etatActuel)
		{
		case Etat::AFFICHAGE:
			affichage.afficher();
			break;

		case Etat::PRISE_INFORMATION:
			string commande;
			cout << "> ";
			getline(cin, commande);
			affichage.setCommande(commande);
			affichage.envoieControleur();
			break;

		}

		switch (etatActuel)
		{
		case Etat::AFFICHAGE:
			etatActuel = Etat::PRISE_INFORMATION;
			break;
		case Etat::PRISE_INFORMATION:
			etatActuel = Etat::AFFICHAGE;
			break;
		}
	}


}
