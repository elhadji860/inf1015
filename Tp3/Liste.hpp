#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include "gsl/span"
#include "cppitertools/range.hpp"
using namespace std;
template <typename T>
class Liste
{
public:
	//TODO: Constructeurs et surcharges d'op�rateurs
	Liste(int capacite, int nElement, std::shared_ptr<std::shared_ptr<T>[]> elements) : capacite_(1), nElements_(0), elements_(make_shared<shared_ptr<T>[]>(1)) {
		capacite_ = capacite;
		nElements_ = nElement;
		elements_ = move(elements);
	}
	Liste()  {
		capacite_ = 1;
		nElements_ = 0;
		elements_ = move(make_unique<shared_ptr<T>[]>(1));
	}

	//TODO: M�thode pour ajouter un �l�ment � la liste
	void changerTailleListeJeux(unsigned nouvelleCapacite)
	{
		assert(nouvelleCapacite >= nElements_); // On ne demande pas de supporter les r�ductions de nombre d'�l�ments.
		unique_ptr<shared_ptr<T>[]> nouvelleListeJeux = make_unique<shared_ptr<T>[]>(nouvelleCapacite);
		// Pas n�cessaire de tester si liste.elements est nullptr puisque si c'est le cas, nElements est n�cessairement 0.
		for (int i : iter::range(nElements_))
			nouvelleListeJeux[i] = elements_[i];



		elements_ = move(nouvelleListeJeux);
		capacite_ = nouvelleCapacite;
	}
	void ajouterElement(shared_ptr<T> element) {
		if (nElements_ == capacite_) {
			changerTailleListeJeux(max(1U, capacite_ * 2));
		}
		elements_[nElements_++] = element;
		
	}
	// Pour size, on utilise le m�me nom que les accesseurs de la biblioth�que standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const { return nElements_; }
	unsigned getCapacite() const { return capacite_; }
	unsigned getNelements() const { return nElements_; }
	void setNelements(int nouvelleValeur) { nElements_ = nouvelleValeur; }
	shared_ptr<shared_ptr<T>[]> getListe() {
		return elements_;
	}
	//TODO: M�thode pour changer la capacit� de la liste
	void changerCapacite(int nouvelleValeur) {
		capacite_ = nouvelleValeur;
	}

	//surcharge de []
	shared_ptr<T> operator[](int i) const {
		return elements_[i];
	}

	
	//TODO: M�thode pour trouver une �l�ment selon un crit�re (lambda).
	shared_ptr<T> trouverElement(function<bool(shared_ptr<T>)> critere) {
		for (unsigned i = 0; i < nElements_; ++i) {
			if (critere(elements_[i])) {
				return elements_[i];
			}
		}
		return nullptr;
	}
private:
	unsigned nElements_;
	unsigned capacite_;
	std::shared_ptr<std::shared_ptr<T>[]> elements_;
	//TODO: Attribut contenant les �l�ments de la liste.
};
