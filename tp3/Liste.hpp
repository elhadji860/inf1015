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
	//TODO: Constructeurs et surcharges d'opérateurs
	Liste() {
		nElements_ = 0;
		capacite_ = 1;
		elements_ = nullptr;
	}
	Liste(unsigned nElement, unsigned capacite, unique_ptr<shared_ptr<T>[]> elements) {
		nElements_ = nElement;
		capacite_ = capacite;
		elements_ = elements;

	}
	//TODO: Méthode pour ajouter un élément à la liste
	void ajouterElement(shared_ptr<T>element) {
		elements_[nElements_] = element;
		++nElements_;
	}
	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO: Méthode pour changer la capacité de la liste
	void changerCapacite(int facteur) {
		capacite_ *= facteur;
	}
	//TODO: Méthode pour trouver une élément selon un critère (lambda).

private:
	unsigned nElements_;
	unsigned capacite_;
	unique_ptr<shared_ptr<T>[]> elements_;
	//TODO: Attribut contenant les éléments de la liste.
};
