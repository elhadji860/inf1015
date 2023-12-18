#pragma once
#include "source.h"

using namespace std;
class Objet 
{
public:
	//constructeur
	Objet(){}
	Objet(string nom, string description, string scriptUse) : nom_(nom), description_(description), scriptUse_(scriptUse){}
	
	//definition de la fonction virtuelle use
	virtual pair<ActionsObjet, string> use() { return { ActionsObjet::RIEN,scriptUse_ }; }

	//setters 
	void setMotCle(vector<string> motCles) { motCles_ = motCles; }
	//getters
	string getNom() const { return nom_; }
	string getDescription() const { return description_; }
	string getScript() const { return scriptUse_; }
	vector<string> getMotCle() const { return motCles_; }

	//destructeur
	virtual ~Objet() = default;

private:
	string nom_;
	string description_;
	string scriptUse_;
	vector<string> motCles_;
};

class ObjetLumiere : public Objet 
{
public:
	//constructeurs
	ObjetLumiere() {}
	ObjetLumiere(string nom, string description, string scriptUse) : Objet(nom, description, scriptUse) {}

	//override de use 
	pair<ActionsObjet, string> use() override
	{
		return {ActionsObjet::LUMIERE, Objet::getScript() };
	}

};

class ObjetCle : public Objet
{
public:
	//constructeurs
	ObjetCle() {  }
	ObjetCle(string nom, string description, string scriptUse) : Objet(nom, description, scriptUse) {}

	//override de use 
	pair<ActionsObjet, string> use() override
	{
		return { ActionsObjet::DEBLOQUE_SALLE, Objet::getScript() };
	}

};