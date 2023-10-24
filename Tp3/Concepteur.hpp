#pragma once
#include <string>
using namespace std;
class Concepteur
{
public:
	//TODO: Un constructeur par défaut et un constructeur paramétré.
	Concepteur(){
		nom_ = "";
		anneeNaissance_ = 0;
		pays_ = "";
	}
	Concepteur(string nom, unsigned anneeNaissance, string pays) {
		nom_ = nom;
		anneeNaissance_ = anneeNaissance;
		pays_ = pays;
	}
	const std::string& getNom() const     { return nom_; }
	void setNom(const std::string& nom)   { nom_ = nom; }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(const std::string& pays) { pays_ = pays; }
	//definition de la copie
	Concepteur& operator=(const Concepteur&  autre) {
		if (this != &autre) {
			nom_ = autre.nom_;
			anneeNaissance_ = autre.anneeNaissance_;
			pays_ = autre.pays_;
		}
		return *this;
	}

	Concepteur(const Concepteur& autre) : Concepteur() {
		*this = autre;
	}
	//surcharge de <<
	friend ostream& operator<< (ostream& o, const Concepteur& concepteur);
private:
	std::string nom_;
	unsigned anneeNaissance_;
	std::string pays_;
};
