#pragma once
#include "Developpeur.hpp"

class ListeDeveloppeurs
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
public:
	ListeDeveloppeurs(Developpeur** element) {
		elements_ = element;
	}

	void afficher() const {
		for (int i = 0; i < nElements_; i++) {
			std::cout << elements_[i]->constGetName()<<std::endl;
		}
	}
	
	void ajouterDeveloppeur(Developpeur* dev) {
		bool isIn = true;
		for (int i = 0; i < nElements_; ++i) {
			if (elements_[i]->constGetName() == dev->constGetName()) {
				isIn = false;
			}
		}
		if (isIn) {
			ajouterDev_(dev);
		}
	}
	void retirerDeveloppeur(Developpeur* dev) {

		for (int i = 0; i < nElements_; ++i) {
			if (dev->constGetName() == elements_[i]->constGetName()) {
				elements_[i] = elements_[nElements_ - 1];
				nElements_ -= 1;
			}
		}
	}

	~ListeDeveloppeurs() {
		delete[] elements_;
	}

private:
	void changementDeTailleDev( int nouvelleValeur, Designer* designer = nullptr) {
		Developpeur** nouveauTableau;
		nouveauTableau = new Developpeur * [nouvelleValeur];

		for (int i = 0; i < nElements_; ++i) {
			nouveauTableau[i] = elements_[i];
		}
		capacite_ *= 2;
		delete[] elements_;
		elements_ = nouveauTableau;

	}
	void ajouterDev_(Developpeur* Dev) {
		if (capacite_ != 0) {
			changementDeTailleDev(2 *capacite_);
			capacite_ *= 2;
			elements_[nElements_] = Dev;
			nElements_ += 1;
		}
		else {
			elements_ = new Developpeur * [1];
			elements_[0] = Dev;
			capacite_ += 1;
			nElements_ += 1;
		}
	}
	unsigned nElements_=0;
	unsigned capacite_=1;
	Developpeur** elements_;
};
