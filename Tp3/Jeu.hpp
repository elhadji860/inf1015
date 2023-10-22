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
	//TODO: un constructeur par d�faut et un constructeur param�tr�.
	const std::string& getTitre() const     { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	//TODO: Pouvoir acc�der � la liste de concepteurs.
	shared_ptr<Liste<Concepteur>> getListe() const {
		shared_ptr<Liste<Concepteur>> ptr = concepteurs_;
		return ptr;
	}

	//TODO: Votre m�thode pour trouver un concepteur selon un crit�re donn� par une lambda, en utilisant la m�thode de Liste.
	shared_ptr<Concepteur> trouverConcepteur(string nom) {
		return (*concepteurs_).trouverElement([nom](shared_ptr<Concepteur> concepteur) {return (*concepteur).getNom() == nom; });
	}

private:
	std::string titre_;
	unsigned anneeSortie_ = 0;
	std::string developpeur_;
	shared_ptr<Liste<Concepteur>> concepteurs_;
};
