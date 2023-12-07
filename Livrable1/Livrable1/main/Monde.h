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
		salleDesTrophes_ = make_shared<Piece>("salle des trophes");
		salleDeClasse_ = make_shared<Piece>("salle de classe");
		atelier_ = make_shared<Piece>("atelier");
		bibliotheque_ = make_shared<Piece>("bibliotheque");
		terrainEntrainement_ = make_shared<Piece>("terrain entrainement");
		observatoire_ = make_shared<Piece>("observatoire");
		laboratoire_ = make_shared<Piece>("laboratoire");

		entree_->setVoisin(sallePrincipale_, AUCUNE, AUCUNE, AUCUNE);
		sallePrincipale_->setVoisin(bibliotheque_, entree_, laboratoire_, salleDeClasse_);
		salleDesTrophes_->setVoisin(AUCUNE, laboratoire_, atelier_, bibliotheque_);
		salleDeClasse_->setVoisin(AUCUNE, AUCUNE, sallePrincipale_, AUCUNE);
		atelier_->setVoisin(terrainEntrainement_, AUCUNE, AUCUNE, salleDesTrophes_);
		bibliotheque_->setVoisin(AUCUNE, sallePrincipale_, salleDesTrophes_, AUCUNE);
		terrainEntrainement_->setVoisin(AUCUNE, atelier_, AUCUNE, observatoire_);
		observatoire_->setVoisin(AUCUNE, AUCUNE, terrainEntrainement_, AUCUNE);
		laboratoire_->setVoisin(salleDesTrophes_, AUCUNE, AUCUNE, sallePrincipale_);

		laboratoire_->setDescription("Un laboratoire lugubre éclairé par une lueur fantomatique,où des étagères croulent sous le poids de fioles mystérieuses. \nL'air est imprégné de magie ancienne,et un autel obscur au centre de la pièce émet un murmure sinistre, \névoquant des expériences interdites.\n\n");
		entree_->setDescription("Une salle d'entrée majestueuse s'ouvre devant vous, \nles murs de pierre ornés de torches vacillantes. \nUn tapis rouge délavé s'étend jusqu'à une porte massive, \nrévélant des fresques anciennes et des statues imposantes qui encadrent l'entrée du donjon, \névoquant une atmosphère de mystère et d'aventure.\n\n");
		salleDesTrophes_->setDescription("Au cœur de la salle des trophées, \ndes étagères imposantes exhibent une collection impressionnante de crânes de créatures fantastiques, \nde griffes venimeuses et de trophées de chasse suspendus. \nLa lueur tamisée des trophées enchantés révèle un musée macabre témoignant des triomphes passés, \ntandis que l'air vibre d'une énergie résiduelle, \nrappelant les exploits des aventuriers qui ont affronté ces redoutables adversaires.\n\n");
		salleDeClasse_->setDescription("Dans la salle de classe, \ndes pupitres soigneusement alignés remplissent l'espace, \néclairés par la lueur douce de lanternes magiques suspendues au plafond voûté. \nAu tableau noir, des schémas magiques s'animent lentement tandis que des parchemins détaillés et des grimoires s'alignent sur les étagères, \ncréant une atmosphère propice à l'apprentissage des arts mystiques.\n\n");
		sallePrincipale_->setDescription("Au cœur du hall principal,\nd'imposantes colonnes de marbre encadrent une entrée majestueuse,\nlaissant filtrer la lueur dorée des lustres suspendus au plafond voûté.\nDes tapis luxueux recouvrent le sol poli,\nmenant à un trône ancestral sur une estrade ornée de motifs complexes,\névoquant la grandeur d'un passé glorieux.\n\n");
		atelier_->setDescription("Dans l'atelier,\nune symphonie d'outils résonne dans l'air chargé d'odeurs de métal et de bois fraîchement coupé.\nLes établis usés sont couverts de projets en cours,\ndes étincelles jaillissent des enclumes,\net les murs sont ornés de parchemins esquissés et de prototypes mécaniques,\ncréant un lieu d'effervescence créative.\n\n");
		bibliotheque_->setDescription("Dans la bibliothèque, \nles étagères en bois sombre s'élèvent jusqu'au plafond, \nchargées de tomes anciens et de parchemins soigneusement alignés.\nLa lueur douce de chandeliers antiques éclaire des fauteuils rembourrés et des tables de lecture, \ninvitant à l'étude et à la contemplation silencieuse.\n\n");
		terrainEntrainement_->setDescription("Dans la salle d'entraînement,\ndes tapis d'entraînement épais recouvrent le sol, \ns'alignant parfaitement sous les rangées de miroirs.\nLe son des poids métalliques s'entrechoquant et des instructeurs donnant des consignes remplit l'air.\nDes mannequins d'entraînement et des équipements divers parsèment l'espace vaste,\ninspirant une énergie dynamique et dédiée à l'amélioration physique.\n\n");
		observatoire_->setDescription("Dans l'observatoire,\nde grandes fenêtres offrent une vue panoramique sur le ciel étoilé,\nlaissant filtrer la lumière faible de la lune et des étoiles.\nDes télescopes complexes pointent vers l'infini céleste,\nentourés de cartes stellaires et de globes célestes.\nDes notes soigneusement annotées jonchent les tables,\nsymboles d'observations astrales et de découvertes cosmiques.\n\n");

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
	void execution(string commande)
	{
		writing = false;
		script = "";

		if (commande == "n")
		{
			if (lieuxEvenements_->getVoisin(Coordonnee::NORD))
			{
				string result;
				personnagePrincipale_->setPosition(lieuxEvenements_->getVoisin(Coordonnee::NORD)->getNom());
				lieuxEvenements_ = lieuxEvenements_->getVoisin(Coordonnee::NORD);
				result = ("vers le nord \n \n\033[93m***" + lieuxEvenements_->getNom()+"***\033[0m\n" + lieuxEvenements_->getDescription());
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
				script = result;
				writing = true;
			}
			else
			{
				script = ("il n'y a rien ici \n\n");
				writing = true;
			}
		}

		if (commande == "s")
		{
			if (lieuxEvenements_->getVoisin(Coordonnee::SUD))
			{
				string result;
				personnagePrincipale_->setPosition(lieuxEvenements_->getVoisin(Coordonnee::SUD)->getNom());
				lieuxEvenements_ = lieuxEvenements_->getVoisin(Coordonnee::SUD);
				result = ("vers le sud \n \n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription());
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

		if (commande == "e")
		{
			if (lieuxEvenements_->getVoisin(Coordonnee::EST))
			{
				string result;
				personnagePrincipale_->setPosition(lieuxEvenements_->getVoisin(Coordonnee::EST)->getNom());
				lieuxEvenements_ = lieuxEvenements_->getVoisin(Coordonnee::EST);
				result = ("vers l'est \n \n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription());
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
		if (commande == "o")
		{
			if (lieuxEvenements_->getVoisin(Coordonnee::OUEST))
			{
				string result;
				personnagePrincipale_->setPosition(lieuxEvenements_->getVoisin(Coordonnee::OUEST)->getNom());
				lieuxEvenements_ = lieuxEvenements_->getVoisin(Coordonnee::OUEST);
				result = ("vers l' Ouest \n \n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription());
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
		if (commande == "look")
		{
			script = "\n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription();
			writing = true;
		}
	}
	

	vector<Action> actionPermises;

private:
	std::shared_ptr<Piece> AUCUNE = nullptr;
	
	shared_ptr<Piece> entree_;
	shared_ptr<Piece> sallePrincipale_;
	shared_ptr<Piece> laboratoire_;
	shared_ptr<Piece> salleDeClasse_;
	shared_ptr<Piece> salleDesTrophes_;
	shared_ptr<Piece> bibliotheque_;
	shared_ptr<Piece> atelier_;
	shared_ptr<Piece> terrainEntrainement_;
	shared_ptr<Piece> observatoire_;

	shared_ptr<Personnage> personnagePrincipale_;

	shared_ptr<Piece> lieuxEvenements_;

	string nom;


};