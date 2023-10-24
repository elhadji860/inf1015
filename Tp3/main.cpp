#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include <iostream>
#include <fstream>
using namespace std;


//fonctions utiles
void separation() {
	static const string ligneSeparation = "\n\033[95m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";
	cout << ligneSeparation;

}
//TODO: Vos surcharges d'opérateur <<

ostream& operator<<(ostream& o, const Concepteur& concepteur) {
	o << "\t" << concepteur.nom_ << ", " << concepteur.anneeNaissance_ << ", " << concepteur.pays_
		<< endl;
	return o;
}

ostream&  operator<<(ostream& o , const Jeu& jeu)
{
	o << "Titre : " << "\033[94m" << jeu.titre_ << "\033[0m" << endl;
	o << "Parution : " << "\033[94m" << jeu.anneeSortie_ << "\033[0m"
		<< endl;
	o << "Développeur :  " << "\033[94m" << jeu.developpeur_ << "\033[0m"
		<< endl;
	o << "Designers du jeu :" << "\033[94m" << endl;
	for (int i = 0; i < jeu.nConcepteur_; ++i) {
		o << *((*jeu.concepteurs_)[i]);
	}
	o << "\033[0m";
	return o;
}

ostream& operator<< (ostream& o, const Liste<Jeu>& lj) {
	static const string ligneSeparation = "\n\033[95m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";
	o << ligneSeparation << endl;
	for (int i = 0; i < lj.getNelements(); ++i)
	{
		o << (*lj[i]);
		o << ligneSeparation << endl;
	}
	return o;
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	Liste<Jeu> lj = creerListeJeux("C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\Tp3\\jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	//TODO: Les l'affichage et l'écriture dans le fichier devraient fonctionner.
	cout << ligneSeparation << "DEBUT" << lj;
	ofstream("C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\tp3\\sortie.txt") << lj;

	//TODO: Compléter le main avec les tests demandés.

	// test de [] sur lj
	separation();
	cout << "test de [] sur lj" << endl;
	cout << lj[2]->getTitre() << endl;
	cout << (*lj[2]->getListe())[1]->getNom() << endl;

	//test de trouverConcepteur
	separation();
	cout << "test de trouverConcepteur" << endl;
	cout << (*lj[0]).trouverConcepteur("Yoshinori Kitase").get() << endl;
	cout << (*lj[1]).trouverConcepteur("Yoshinori Kitase").get() << endl;

	//Test de copie
	separation();
	cout << "test des copies" << endl;
	Jeu copieJeu = *lj[2];
	((*(copieJeu.getListe())).getListe())[1] = (*lj[0]->getListe())[5];
	cout << copieJeu << endl;
	cout << *lj[2] << endl;
	separation();
	cout << ((*(copieJeu.getListe())).getListe())[1].get() << "=" << (*lj[0]->getListe())[5].get() << endl;

	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}