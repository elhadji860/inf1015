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
	Liste(int capacite, int nElement, unique_ptr<shared_ptr<T>> elements) : capacite_(1), nElements_(0), elements_(make_unique<shared_ptr<T>>[1]){
		capacite_ = capacite;
		nElements_ = nElement;
		elements_ = elements;
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
		if (nElements_ == capacite_)
			changerTailleListeJeux(max(1U, capacite_ * 2));
		elements_[nElements_++] = element;
	}
	// Pour size, on utilise le m�me nom que les accesseurs de la biblioth�que standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const { return nElements_; }
	unsigned getCapacite() const { return capacite_; }
	std::unique_ptr<std::shared_ptr<T>[]>& getElements{ return elements_;}
	//TODO: M�thode pour changer la capacit� de la liste
	void changerCapacite(int nouvelleValeur) {
		capacite_ = nouvelleValeur;
	}
	//
	shared_ptr<T>& operator[](int position) {
		return elements_[position];
	};
	// 
	//TODO: M�thode pour trouver une �l�ment selon un crit�re (lambda).
	template<typename U>
	T trouverElement(const U critere, function<U(T)> fonction) {
		int position = 0;
		for (int i = 0; i < nElements_, ++i) {
			if (critere = fonction(*elements_[i]) {
				return elements_[i];
			}
		}
		
	}
private:
	unsigned nElements_;
	unsigned capacite_;
	std::unique_ptr<std::shared_ptr<T>[]> elements_;
	//TODO: Attribut contenant les �l�ments de la liste.
};
