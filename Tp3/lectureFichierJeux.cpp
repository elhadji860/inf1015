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
gsl::span<shared_ptr<Jeu>> spanListeJeux(const Liste<Jeu>& liste)
{
	return gsl::span(liste.getElements(), liste.getCapacite());
}

shared_ptr<Concepteur> chercherConcepteur(Liste<Jeu>& listeJeux, string nom)
{
	
		for (const Jeu* j : spanListeJeux(listeJeux)) {
			// Normalement on voudrait retourner un pointeur const, mais cela nous
			// empêcherait d'affecter le pointeur retourné lors de l'appel de cette
			// fonction.
			for (shared_ptr<Concepteur> d : spanListeDesigners(j->designers)) {
				if (d->nom == nom)
					return d;
			}
		}
		return nullptr;
}

shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj, istream& f)
{
	string nom = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays = lireString(f);

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).
	shared_ptr<Concepteur> concepteur = make_shared<Concepteur>();
	concepteur->setNom(nom);
	concepteur->setAnneeNaissance(anneeNaissance);
	concepteur->setPays(pays);

	//cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return concepteur;
}

shared_ptr<Jeu> lireJeu(istream& f, Liste<Jeu>& lj)
{
	string titre = lireString(f);
	unsigned anneeSortie = lireUint16(f);
	string developpeur = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	for (unsigned int i = 0; i < nConcepteurs; i++)
		lireConcepteur(lj, f);
	shared_ptr<Jeu> jeu = make_shared<Jeu>();
	jeu->setTitre(titre);
	jeu->setAnneeSortie(anneeSortie);
	jeu->setDeveloppeur(developpeur);
	lj.ajouterElement(jeu);
	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return jeu;
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compléter la fonction.
	Liste<Jeu> listeJeux;
	for ([[maybe_unused]] int i : iter::range(nElements))
		shared_ptr<Jeu>jeu = lireJeu(f, listeJeux);
	return listeJeux;
}
