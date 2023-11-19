#pragma once
#include <gsl/pointers>
#include "Noeud.hpp"
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO: Constructeur(s).
	Noeud(const T& element) { donnee_ = element; }
private:
	//TODO: Attributs d'un noeud.
	inline static constexpr Noeud* past_end = nullptr;
	Noeud<T>* suivant_ = past_end;
	Noeud<T>*precedent_ = past_end;
	T donnee_;
};
