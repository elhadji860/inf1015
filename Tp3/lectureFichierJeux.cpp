// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
#include "iostream"
using namespace std;

#pragma region "Fonctions de lecture de base"
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion


shared_ptr<Concepteur> chercherConcepteur(Liste<Jeu>& lj, string nom)
{
	shared_ptr<Concepteur> ptr_Concepteur = nullptr;
	if (lj.getNelements() == 0) {
		return ptr_Concepteur;
	}

	for (unsigned i = 0; i < lj.getNelements(); ++i) {
		for (unsigned j = 0; j < (*(*lj[i]).getListe()).getNelements(); ++j) {
			if ((*lj[i]).trouverConcepteur(nom) != nullptr) {
				ptr_Concepteur = (*lj[i]).trouverConcepteur(nom);
			}
		}
	}
	return ptr_Concepteur;
}

shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj, istream& f)
{
	string nom = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays = lireString(f);

	//TODO: Compl�ter la fonction (�quivalent de lireDesigner du TD2).
	shared_ptr<Concepteur> concepteur = make_shared<Concepteur>();
	concepteur->setNom(nom);
	concepteur->setAnneeNaissance(anneeNaissance);
	concepteur->setPays(pays);

	//cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant � voir que le code fourni lit bien les jeux.
	return concepteur;
}

void lireJeu(istream& f, Liste<Jeu>& lj)
{
	string titre = lireString(f);
	unsigned anneeSortie = lireUint16(f);
	string developpeur = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	//TODO: Compl�ter la fonction (�quivalent de lireJeu du TD2).
	for (unsigned int i = 0; i < nConcepteurs; i++)
		lireConcepteur(lj, f);
	shared_ptr<Jeu> jeu = make_shared<Jeu>();
	jeu->setTitre(titre);
	jeu->setAnneeSortie(anneeSortie);
	jeu->setDeveloppeur(developpeur);
	lj.ajouterElement(move(jeu));
	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant � voir que le code fourni lit bien les jeux.
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compl�ter la fonction.
	Liste<Jeu> listeJeux;
	for ([[maybe_unused]] int i : iter::range(nElements))
	     lireJeu(f, listeJeux);
	return listeJeux;
}
