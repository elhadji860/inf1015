#pragma once
#include "Controleur.h"
#include "Monde.h"

using namespace std;

class Affichage
{
public:
	Affichage(shared_ptr<Monde> monde, shared_ptr<Controleur> controleur) : monde_(monde), controleur_(controleur)
	{
		actionsPermises_ = { Action::DEPLACEMENT, Action::INFORMATION };
		disclaimer = "***DISCLAIMER*** \n\033[91mLes descriptions des pieces fournies n'ont pas ete entierement ecrite par les membres de notre groupe. \nElles sont en grandes parties issues de jeux deja existants\033[0m\n\n";
		textDebut = "\033[92m***POLY AVENTURE***\033[0m \nBienvenue dans un batiment de poly fantastique\n\n ***aide commande*** \n	n : aller vers le nord \n	s : aller vers le sud \n	o : aller vers l'ouest \n	e : aller vers l'est \n\n  vous vous trouvez dans la salle d'entree GLHF \n\n";
		script_ = disclaimer + textDebut + "\033[93m***" + monde_->getLieuxEvent()->getNom() + "***\033[0m\n" + monde_->getLieuxEvent()->getDescription();
	};


	//definitions des setters
	void setScript(string script) { script_ = script; }
	void setCommande(string commande) { commande_ = commande; }

	//fonctions pour les interactions 
	void afficher() 
	{ 
		if (controleur_->writing) {
			script_ = controleur_->script;
		}
		if (monde_->writing) {
			actionsPermises_ = monde_->actionPermises;
			script_ = monde_->script;
		}
		cout << script_; 
	
	}
	void envoieControleur() { 
		monde_->writing = false;
		controleur_->writing = false;
		controleur_->gestionCommande(commande_, actionsPermises_); }


private:
	shared_ptr<Controleur> controleur_;
	shared_ptr<Monde> monde_;
	string script_;
	string commande_;
	vector<Action> actionsPermises_;
	string disclaimer;
	string textDebut;

};