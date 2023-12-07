#pragma once
#include "Personnage.h"

using namespace std;



class Piece
{
public:
	Piece() {}
	Piece(string nom) { nom_ = nom; }

	//definition de setters
	void setVoisin(shared_ptr<Piece> nord, shared_ptr<Piece> sud, shared_ptr<Piece> est, shared_ptr<Piece> ouest) {
		pieceNord_ = nord;
		pieceSud_ = sud;
		pieceOuest_ = ouest;
		pieceEst_ = est;

		boussole_ = { {Coordonnee::NORD, pieceNord_},{Coordonnee::SUD, pieceSud_},{Coordonnee::OUEST, pieceOuest_},{Coordonnee::EST, pieceEst_} };
	}
	void setDescription(string description) { description_ = description; }

	//fonction pour les interactions
	void enleverPersonnage(shared_ptr<Personnage> personnage) {
		auto it = remove_if(personnagesPresents.begin(), personnagesPresents.end(), [=](shared_ptr<Personnage> perso) {return personnage->getNom() == perso->getNom(); });
		personnagesPresents.erase(it);
	};

	//getters
	string getNom() const { return nom_; }
	string getDescription() const { return description_; }
	shared_ptr<Piece> getVoisin(Coordonnee coordonnee) { return boussole_[coordonnee]; }


private:
	std::shared_ptr<Piece> AUCUNE = nullptr;

	string nom_;
	string description_;

	shared_ptr<Piece> pieceNord_ = AUCUNE;
	shared_ptr<Piece> pieceSud_ = AUCUNE;
	shared_ptr<Piece> pieceOuest_ = AUCUNE;
	shared_ptr<Piece> pieceEst_ = AUCUNE;

	map<Coordonnee, shared_ptr<Piece>> boussole_;

	vector<shared_ptr<Personnage>> personnagesPresents;
};