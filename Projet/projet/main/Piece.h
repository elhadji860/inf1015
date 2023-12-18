#pragma once
#include "Personnage.h"
#include "Objet.h"

using namespace std;



class Piece
{
public:
	Piece() {}
	Piece(string nom, bool accessible = true, bool estEclair = true) : estAccessible_ (accessible), nom_(nom), estEclairee_(estEclair) {}

	//definition de setters
	void setVoisin(shared_ptr<Piece> nord, shared_ptr<Piece> sud, shared_ptr<Piece> est, shared_ptr<Piece> ouest) {
		pieceNord_ = nord;
		pieceSud_ = sud;
		pieceOuest_ = ouest;
		pieceEst_ = est;

		boussole_ = { {Coordonnee::NORD, pieceNord_},{Coordonnee::SUD, pieceSud_},{Coordonnee::OUEST, pieceOuest_},{Coordonnee::EST, pieceEst_} };
	}
	void setDescription(string description) { description_ = description; }
	void setObjets(vector<shared_ptr<Objet>> objetsPresents) { objetsPresent_ = objetsPresents; }
	void setLienEclair(vector<shared_ptr<Piece>> lienEclair) { liensEclairage_ = lienEclair; };
	void setSalleDeb(vector<shared_ptr<Piece>> deblocable) { salleDeblocables_ = deblocable; }
	

	//getters
	string getNom() const { return nom_; }
	string getDescription() const { return description_; }
	shared_ptr<Piece> getVoisin(Coordonnee coordonnee) 
	{ 
		if (boussole_[coordonnee])
		{
			if (boussole_[coordonnee]->estAccessible_)
				return boussole_[coordonnee];
		}
			return AUCUNE;
	}
	bool getEclair() const { return estEclairee_; }
	bool getAcccess() const { return estAccessible_; }
	vector<shared_ptr<Objet>> getObjetsPresent() { return objetsPresent_; }

	//fonction pour les interaction
	string useRetroAction(ActionsObjet action)
	{
		string script;
		switch (action)
		{
		case ActionsObjet::RIEN:
			break;
		case ActionsObjet::DEBLOQUE_SALLE:
			if (salleDeblocables_.size())
			{
				for (auto x : salleDeblocables_)
				{
					if (!(x->estAccessible_))
					{
						x->estAccessible_ = true;
						script += x->getNom() + " est desormais accessible\n";
					}
				}
			}
			break;
		case ActionsObjet::LUMIERE:
			if (liensEclairage_.size())
			{
				for (auto x : liensEclairage_)
				{
					if (x->estEclairee_)
					{
						x->estEclairee_ = false;
						script += x->getNom() + " est plongee dans le noir\n";
					}
					else
					{
						x->estEclairee_ = true;
						script += x->getNom() + " est eclairee\n";
					}
				}
			}
			break;
		
		}
		return script;
	}



private:
	std::shared_ptr<Piece> AUCUNE = nullptr;

	string nom_;
	string description_;
	bool estAccessible_;
	bool estEclairee_;

	shared_ptr<Piece> pieceNord_ = AUCUNE;
	shared_ptr<Piece> pieceSud_ = AUCUNE;
	shared_ptr<Piece> pieceOuest_ = AUCUNE;
	shared_ptr<Piece> pieceEst_ = AUCUNE;
	map<Coordonnee, shared_ptr<Piece>> boussole_;

	vector<shared_ptr<Objet>> objetsPresent_;
	vector<shared_ptr<Piece>> liensEclairage_;
	vector<shared_ptr<Piece>> salleDeblocables_;
};

