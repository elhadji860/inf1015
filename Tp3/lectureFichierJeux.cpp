// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
#include "iostream"
#include "Jeu.hpp"
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

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).
	shared_ptr<Concepteur> ptrConcepteur = chercherConcepteur(lj, nom);
	if (ptrConcepteur == nullptr) {
		ptrConcepteur = make_shared<Concepteur>(Concepteur(nom,anneeNaissance,pays));
	}
	return ptrConcepteur;
}

void lireJeu(istream& f, Liste<Jeu>& lj)
{
	string titre = lireString(f);
	unsigned anneeSortie = lireUint16(f);
	string developpeur = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	
	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	shared_ptr<Liste<Concepteur>> concepteurs = make_shared<Liste<Concepteur>>();
	shared_ptr<Jeu> jeu = make_shared<Jeu>(Jeu(nConcepteurs,titre,anneeSortie,developpeur,move(concepteurs)));

	for (unsigned int i = 0; i < nConcepteurs; i++)
		jeu->getListe()->ajouterElement(lireConcepteur(lj, f));
	
	lj.ajouterElement(move(jeu));
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compléter la fonction.
	Liste<Jeu> listeJeux;
	listeJeux.setNelements(0);
	for ([[maybe_unused]] int i : iter::range(nElements))
	     lireJeu(f, listeJeux);
	return listeJeux;
}
