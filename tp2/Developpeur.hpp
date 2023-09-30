#pragma once
#include <string>
#include "ListeJeux.hpp"
#include "Jeu.hpp"
#include "iostream"
#include "vector"


class Developpeur
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	//TODO: Les méthodes à faire...
public:

	Developpeur(std::pair<std::string, ListeJeux> paireNomJeux) {
		paireNomJeux_ = paireNomJeux;
	}
	const std::string constGetName() const {
		return paireNomJeux_.first;
	}

	std::vector<Jeu*> jeuxDeveloppe(ListeJeux listeJeu) {
		std::vector<Jeu*> array_jeu;
		
		for (int i = 0; i < listeJeu.nElements; ++i) {
			if (listeJeu.elements[i]->developpeur == getName()) {
				array_jeu.push_back(listeJeu.elements[i]);
			}
		}
		return array_jeu;
	}
	void majListe(ListeJeux listeJeu) {
		std::vector<Jeu*> jeuDev = jeuxDeveloppe(listeJeu);
		for (int i = 0; i<jeuDev.size(); ++i) {
			paireNomJeux_.second.elements[i]=jeuDev[i];
			paireNomJeux_.second.nElements += 1;
		}
	}

	void const afficherJeu() const {
		for (int i = 0; i < paireNomJeux_.second.nElements; ++i) {
			std::cout << paireNomJeux_.second.elements[i]->titre << std::endl;
			
		}
		std::cout << "" << std::endl;
	}
	~Developpeur() {
		delete[] paireNomJeux_.second.elements;
	}
private:

	std::pair<std::string, ListeJeux> paireNomJeux_;
	std::string getName() {
		return paireNomJeux_.first;
	}
};

