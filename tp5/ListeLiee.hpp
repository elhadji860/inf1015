#pragma once
#include "iterateur.hpp"
#include "gsl/gsl_assert"
#include "Noeud.hpp"

template<typename T> class Iterateur;
template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	//TODO: La construction par défaut doit créer une liste vide valide.
	ListeLiee(): tete_(Noeud<T>::past_end), queue_(Noeud<T>::past_end), taille_(0){}
	~ListeLiee()
	{
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		while (tete_->suivant_ != Noeud<T>::past_end) {
			Noeud<T>* ancienneTete = tete_;
			
			tete_ = tete_->suivant_;
			tete_->precedent_ = Noeud<T>::past_end;
			
			ancienneTete->suivant_ = Noeud<T>::past_end;
			
			delete ancienneTete;
			--taille_;
		}
		delete queue_;
		
	}

	bool estVide() const  { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin()  { return {to_address(tete_)}; }
	iterator end()    { return {to_address(queue_->suivant_)}; }

	// Ajoute à la fin de la liste.
	void push_back(const T& item)
	{
		//TODO: Vous devez créer un nouveau noeud en mémoire.
		//TODO: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
	
		Noeud<T>* nouveau = new Noeud<T>(item);
		if (estVide()) {
			tete_ = nouveau;
			queue_ = nouveau;
			taille_++;
		}
		else {
			Noeud<T>* ancienneQueue = queue_;
			
			queue_ = nouveau;
			nouveau->precedent_ = ancienneQueue;

			ancienneQueue->suivant_ = nouveau;

			taille_++;
		}
	}

	// Insère avant la position de l'itérateur.
	iterator insert(iterator it, const T& item)
	{
		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO:
		// 1. Créez un nouveau noeud initialisé avec item.
		Noeud<T>* nouveau = new Noeud<T>(item);

		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		nouveau->suivant_ = (it.position_);
		nouveau->precedent_ = (it.position_)->precedent_;

		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		nouveau->suivant_->precedent_ = nouveau;

		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		nouveau->precedent_->suivant_ = nouveau;

		// 5. Incrémentez la taille de la liste.
		++taille_;

		// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
		return iterator(nouveau);
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		//TODO: Enlever l'élément à la position de l'itérateur.
		//  1. Le pointeur vers le Noeud à effacer est celui dans l'itérateur.
		//  2. Modifiez l'attribut suivant_ du noeud précédent pour que celui-ci
		//     pointe vers le noeud suivant la position de l'itérateur (voir 1.).
		Noeud<T>* result;

		if (((it.position_)->donnee_).getNom() == (tete_->donnee_).getNom()) {
			Noeud<T>* ancienneTete = tete_;

			tete_ = ancienneTete->suivant_;
			(tete_->precedent_) = Noeud<T>::past_end;

			delete ancienneTete;
			return iterator(tete_);
		}

		else {
			((it.position_)->precedent_)->suivant_ = (it.position_)->suivant_;
		}
		//  3. Modifiez l'attribut precedent_ du noeud suivant la position de
		//     l'itérateur pour que celui-ci pointe vers le noeud précédent
		//     de la position de l'itérateur (voir 1.).
		if (((it.position_)->donnee_).getNom() == (queue_->donnee_).getNom()) {
			Noeud<T>* ancienneQueue = queue_;

			queue_ = ancienneQueue->precedent_;
			(queue_->suivant_) = Noeud<T>::past_end;

			delete ancienneQueue;
			return iterator(queue_);
		}

		else {
			((it.position_)->suivant_)->precedent_ = (it.position_)->precedent_;
			result = ((it.position_)->suivant_);
		}
		//  4. Désallouez le Noeud à effacer (voir 1.).
		delete it.position_;
		//  5. Décrémentez la taille de la liste
		--taille_;
		//  6. Retournez un itérateur vers le suivant du Noeud effacé.
		return iterator(result);
		//TODO: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

private:
	gsl::owner<Noeud<T>*> tete_;  //NOTE: Vous pouvez changer le type si vous voulez.
	Noeud<T>* queue_;
	unsigned taille_;
};
