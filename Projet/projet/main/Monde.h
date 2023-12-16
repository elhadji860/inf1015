#pragma once
#include "Piece.h"

using namespace std;


class Monde
{
public:
	Monde()
	{
		entree_ = make_shared<Piece>("entree");
		sallePrincipale_ = make_shared<Piece>("salle Principale");
		salleDeClasse_ = make_shared<Piece>("salle de classe");
		bibliotheque_ = make_shared<Piece>("bibliotheque");
		laboratoire_ = make_shared<Piece>("laboratoire");

		entree_->setVoisin(sallePrincipale_, AUCUNE, AUCUNE, AUCUNE);
		sallePrincipale_->setVoisin(bibliotheque_, entree_, laboratoire_, salleDeClasse_);
		salleDeClasse_->setVoisin(AUCUNE, AUCUNE, sallePrincipale_, AUCUNE);
		bibliotheque_->setVoisin(AUCUNE, sallePrincipale_, AUCUNE, AUCUNE);
		laboratoire_->setVoisin(AUCUNE, AUCUNE, AUCUNE, sallePrincipale_);

		laboratoire_->setDescription("Un laboratoire lugubre eclaire par une lueur fantomatique,ou des etageres croulent sous le poids de fioles mysterieuses. \nL'air est impregne de magie ancienne,et un autel obscur au centre de la piece emet un murmure sinistre, \nevoquant des experiences interdites.\n\n");
		entree_->setDescription("Une salle d'entree majestueuse s'ouvre devant vous, \nles murs de pierre ornes de torches vacillantes. \nUn tapis rouge delave s'etend jusqu'a une porte massive, \nrevelant des fresques anciennes et des statues imposantes qui encadrent l'entree du donjon, \nevoquant une atmosphere de mystere et d'aventure.\n\n");
		salleDeClasse_->setDescription("Dans la salle de classe, \ndes pupitres soigneusement alignes remplissent l'espace, \neclaires par la lueur douce de lanternes magiques suspendues au plafond voute. \nAu tableau noir, des schemas magiques s'animent lentement tandis que des parchemins detailles et des grimoires s'alignent sur les etageres, \ncreant une atmosphere propice a l'apprentissage des arts mystiques.\n\n");
		sallePrincipale_->setDescription("Au coeur du hall principal,\nd'imposantes colonnes de marbre encadrent une entree majestueuse,\nlaissant filtrer la lueur doree des lustres suspendus au plafond voute.\nDes tapis luxueux recouvrent le sol poli,\nmenant a un trone ancestral sur une estrade ornee de motifs complexes,\nevoquant la grandeur d'un passe glorieux.\n\n");
		bibliotheque_->setDescription("Dans la bibliotheque, \nles etageres en bois sombre s'elevent jusqu'au plafond, \nchargees de tomes anciens et de parchemins soigneusement alignes.\nLa lueur douce de chandeliers antiques eclaire des fauteuils rembourres et des tables de lecture, \ninvitant a l'etude et a la contemplation silencieuse.\n\n");

		nom = "poly fantastique";
		personnagePrincipale_ = make_shared<Personnage>(entree_->getNom(), "heros");
		lieuxEvenements_ = entree_;
		actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };


	};
	//definition de setters


	//definition de getters
	shared_ptr<Piece> getLieuxEvent() const { return lieuxEvenements_; }

	//fonctions pour les interactions
	string script;
	bool writing = false;
	bool commandeUnitaire;
	void executionMouvement(string commande)
	{
		string stringCoordonnee;
		Coordonnee nouvelleCoordonnee;
		if(commande == "o")
		{
			nouvelleCoordonnee = Coordonnee::OUEST;
			stringCoordonnee = "ouest";
		}
		if (commande == "s")
		{
			nouvelleCoordonnee = Coordonnee::SUD;
			stringCoordonnee = "sud";
		}
		if (commande == "n")
		{
			nouvelleCoordonnee = Coordonnee::NORD;
			stringCoordonnee = "nord";
		}
		if (commande == "e")
		{
			nouvelleCoordonnee = Coordonnee::EST;
			stringCoordonnee = "est";
		}
		if (lieuxEvenements_->getVoisin(nouvelleCoordonnee))
		{
			string result;
			personnagePrincipale_->setPosition(lieuxEvenements_->getVoisin(nouvelleCoordonnee)->getNom());
			lieuxEvenements_ = lieuxEvenements_->getVoisin(nouvelleCoordonnee);
			result = ("vers l'" +stringCoordonnee+" \n \n\033[93m * **" + lieuxEvenements_->getNom() + " * **\033[0m\n" + lieuxEvenements_->getDescription());
			actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
			script = result;
			writing = true;
		}
		else
		{
			script = ("il n'y a rien ici\n\n");
			writing = true;
		}
	}

	void executionCommandeSimple(string commande)
	{
		writing = false;
		script = "";

		if (commande == "o"||commande=="e"||commande=="s"||commande =="n")
		{
			executionMouvement(commande);
		}

		if (commande == "look")
		{
			if (commandeUnitaire)
			{
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
				script = "\n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription();
				writing = true;
			}
			else
			{
				actionPermises = { Action::INFORMATION_OBJET };
				writing = true;
			}
		}
		if (commande == "use")
		{
			if (commandeUnitaire)
			{
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
				script = "il manque un argument";
				writing = true;
			}
			else
			{
				actionPermises = { Action::USE_OBJET };
				writing = true;
			}
		}
	}


	vector<Action> actionPermises;

private:
	std::shared_ptr<Piece> AUCUNE = nullptr;

	shared_ptr<Piece> entree_;
	shared_ptr<Piece> sallePrincipale_;
	shared_ptr<Piece> laboratoire_;
	shared_ptr<Piece> salleDeClasse_;
	shared_ptr<Piece> bibliotheque_;

	shared_ptr<Personnage> personnagePrincipale_;

	shared_ptr<Piece> lieuxEvenements_;

	string nom;

	


};