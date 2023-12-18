#pragma once
#include "Controleur.h"
#include "Monde.h"

using namespace std;

class Affichage
{
public:
	Affichage(shared_ptr<Monde> monde, shared_ptr<Controleur> controleur) : monde_(monde), controleur_(controleur)
	{
		disclaimer = "***DISCLAIMER*** \n\033[91mLes descriptions des pieces fournies n'ont pas ete entierement ecrite par les membres de notre groupe. \nElles sont en grandes parties issues de jeux deja existants\033[0m\n\n";
		textDebut = "\033[92m***POLY AVENTURE***\033[0m \nBienvenue dans un batiment de poly fantastique\n\n ***aide commande*** \n	n : aller vers le nord \n	s : aller vers le sud \n	o : aller vers l'ouest \n	e : aller vers l'est \n	look : obtenir des informations\n	use :  utiliser un objet\n	exit :  arreter le jeu \n\n  vous vous trouvez dans la salle d'entree GLHF \n\n";
		script_ = disclaimer + textDebut + "\033[93m***" + monde_->getLieuxEvent()->getNom() + "***\033[0m\n" + monde_->getLieuxEvent()->getDescription();
		if (monde_->getLieuxEvent()->getEclair())
		{
			script_ += "vous remarquez :\n";
			for (auto x : monde_->getLieuxEvent()->getObjetsPresent())
			{
				script_ += "	un(e) " + x->getNom() + '\n';
			}
			script_ += '\n';
		}
		else
		{
			script_ += "la piece est sombre vous ne distinguez rien\n\n";
		}

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
			script_ = monde_->script;
		}
		cout << script_;

	}
	void envoieControleur() {
		monde_->writing = false;
		controleur_->writing = false;
		commande_.erase(remove(commande_.begin(), commande_.end(), ' '), commande_.end());
		
		if (commande_ == "exit")
		{
			cout << "fin du jeu";
			exit(0);
		}
		if (commande_.size() > 2) 
		{
			if (commande_== "use")
			{
				monde_->commandeUnitaire = true;
				controleur_->gestionCommande(commande_);
			}
			else if (commande_ == "look")
			{
				monde_->commandeUnitaire = true;
				controleur_->gestionCommande(commande_);
			}

			else if (commande_.substr(0, 3) == "use")
			{
				monde_->commandeUnitaire = false;
				controleur_->gestionCommande("use");
				commande_ = commande_.substr(2, commande_.size());
				monde_->writing = false;
				controleur_->writing = false;
				controleur_->gestionCommande(commande_);
			}
			else if (commande_.substr(0, 4) == "look")
			{
				monde_->commandeUnitaire = false;
				controleur_->gestionCommande("look");
				monde_->writing = false;
				controleur_->writing = false;
				controleur_->gestionCommande(commande_);
			}
			else
			{
				monde_->commandeUnitaire = true;
				controleur_->gestionCommande(commande_);
			}
		}
		
		else
		{
			monde_->commandeUnitaire = true;
			controleur_->gestionCommande(commande_);
		}
			
		
	}


private:
	shared_ptr<Controleur> controleur_;
	shared_ptr<Monde> monde_;
	string script_;
	string commande_;
	string disclaimer;
	string textDebut;

};