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

	const std::string& getTitre() const     { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	//TODO: Pouvoir accéder à la liste de concepteurs.

	//TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	function<string(Concepteur)> critereConcepteur = [](Concepteur concepteur) {return concepteur.getNom(); };
	Concepteur trouverConcepteur(string nom) {
		concepteurs_.trouverElement<string>(string U)
	}
private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;
	Liste<Concepteur> concepteurs_;
};
