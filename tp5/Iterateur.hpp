#pragma once
#include "Noeud.hpp"
#include "gsl/gsl_assert"
template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO: Constructeur(s).
	Iterateur(Noeud <T>* element = Noeud<T>::past_end): position_(element){}

	void avancer()
	{
		Expects(position_ != nullptr);
		//TODO: changez la position de l'itérateur pour le noeud suivant
		Noeud<T>* suivant = (*position_).suivant_;
		position_ = suivant;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != nullptr);
		//TODO: Changez la position de l'itérateur pour le noeud précédent
		Noeud<T>* precedent = (position_)->precedent_;
		position_ = precedent;
	}
	T& operator*()
	{
		return position_->donnee_;
	}

	void operator++(){
		avancer();
	}
	//TODO: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	bool operator==(const Iterateur<T>& it) const = default;
private:
	Noeud<T>* position_;
};
