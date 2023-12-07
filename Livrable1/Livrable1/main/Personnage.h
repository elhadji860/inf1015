#pragma once
#include "provider.h"

using namespace std;

class Personnage
{
public:
	Personnage(string position, string nom) : position_(position), nom_(nom) {}

	//definition des setters
	void setPosition(string nouvellePosition) { position_ = nouvellePosition; }

	//definition des getters
	string getPosition() const { return position_; }
	string getNom() const { return nom_; }

private:
	string position_;
	string nom_;
};