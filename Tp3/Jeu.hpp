#pragma once
#include "Concepteur.hpp"
#include <string>
#include <memory>
#include <functional>
#include "Liste.hpp"
using namespace std;
class Jeu
{
public:
	//TODO: un constructeur par défaut et un constructeur paramétré.
	Jeu() { nConcepteur_ = 0; developpeur_ = ""; anneeSortie_ = 0; concepteurs_ = nullptr; titre_ = ""; }
	Jeu(unsigned int nConcepteur, string titre, unsigned int anneeSortie, string developpeur, shared_ptr<Liste<Concepteur>> concepteurs ){
		developpeur_ = developpeur;
		nConcepteur_ = nConcepteur;
		titre_ = titre;
		anneeSortie_ = anneeSortie;
		concepteurs_ = move(concepteurs);
	}
	const std::string& getTitre() const     { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }
	//TODO: Pouvoir accéder à la liste de concepteurs.
	shared_ptr<Liste<Concepteur>> getListe() const {
		shared_ptr<Liste<Concepteur>> ptr = concepteurs_;
		return ptr;
	}
    //
	friend ostream& operator<<(ostream& o, const Jeu jeu);
	//TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	shared_ptr<Concepteur> trouverConcepteur(string nom) {
		return (*concepteurs_).trouverElement([nom](shared_ptr<Concepteur> concepteur) {return (*concepteur).getNom() == nom; });
	}

private:
	std::string titre_;
	unsigned anneeSortie_ = 0;
	std::string developpeur_;
	shared_ptr<Liste<Concepteur>> concepteurs_;
	unsigned nConcepteur_;
};
