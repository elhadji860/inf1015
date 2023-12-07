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

		laboratoire_->setDescription("Un laboratoire lugubre �clair� par une lueur fantomatique,o� des �tag�res croulent sous le poids de fioles myst�rieuses. \nL'air est impr�gn� de magie ancienne,et un autel obscur au centre de la pi�ce �met un murmure sinistre, \n�voquant des exp�riences interdites.\n\n");
		entree_->setDescription("Une salle d'entr�e majestueuse s'ouvre devant vous, \nles murs de pierre orn�s de torches vacillantes. \nUn tapis rouge d�lav� s'�tend jusqu'� une porte massive, \nr�v�lant des fresques anciennes et des statues imposantes qui encadrent l'entr�e du donjon, \n�voquant une atmosph�re de myst�re et d'aventure.\n\n");
		salleDesTrophes_->setDescription("Au c�ur de la salle des troph�es, \ndes �tag�res imposantes exhibent une collection impressionnante de cr�nes de cr�atures fantastiques, \nde griffes venimeuses et de troph�es de chasse suspendus. \nLa lueur tamis�e des troph�es enchant�s r�v�le un mus�e macabre t�moignant des triomphes pass�s, \ntandis que l'air vibre d'une �nergie r�siduelle, \nrappelant les exploits des aventuriers qui ont affront� ces redoutables adversaires.\n\n");
		salleDeClasse_->setDescription("Dans la salle de classe, \ndes pupitres soigneusement align�s remplissent l'espace, \n�clair�s par la lueur douce de lanternes magiques suspendues au plafond vo�t�. \nAu tableau noir, des sch�mas magiques s'animent lentement tandis que des parchemins d�taill�s et des grimoires s'alignent sur les �tag�res, \ncr�ant une atmosph�re propice � l'apprentissage des arts mystiques.\n\n");
		sallePrincipale_->setDescription("Au c�ur du hall principal,\nd'imposantes colonnes de marbre encadrent une entr�e majestueuse,\nlaissant filtrer la lueur dor�e des lustres suspendus au plafond vo�t�.\nDes tapis luxueux recouvrent le sol poli,\nmenant � un tr�ne ancestral sur une estrade orn�e de motifs complexes,\n�voquant la grandeur d'un pass� glorieux.\n\n");
		atelier_->setDescription("Dans l'atelier,\nune symphonie d'outils r�sonne dans l'air charg� d'odeurs de m�tal et de bois fra�chement coup�.\nLes �tablis us�s sont couverts de projets en cours,\ndes �tincelles jaillissent des enclumes,\net les murs sont orn�s de parchemins esquiss�s et de prototypes m�caniques,\ncr�ant un lieu d'effervescence cr�ative.\n\n");
		bibliotheque_->setDescription("Dans la biblioth�que, \nles �tag�res en bois sombre s'�l�vent jusqu'au plafond, \ncharg�es de tomes anciens et de parchemins soigneusement align�s.\nLa lueur douce de chandeliers antiques �claire des fauteuils rembourr�s et des tables de lecture, \ninvitant � l'�tude et � la contemplation silencieuse.\n\n");
		terrainEntrainement_->setDescription("Dans la salle d'entra�nement,\ndes tapis d'entra�nement �pais recouvrent le sol, \ns'alignant parfaitement sous les rang�es de miroirs.\nLe son des poids m�talliques s'entrechoquant et des instructeurs donnant des consignes remplit l'air.\nDes mannequins d'entra�nement et des �quipements divers pars�ment l'espace vaste,\ninspirant une �nergie dynamique et d�di�e � l'am�lioration physique.\n\n");
		observatoire_->setDescription("Dans l'observatoire,\nde grandes fen�tres offrent une vue panoramique sur le ciel �toil�,\nlaissant filtrer la lumi�re faible de la lune et des �toiles.\nDes t�lescopes complexes pointent vers l'infini c�leste,\nentour�s de cartes stellaires et de globes c�lestes.\nDes notes soigneusement annot�es jonchent les tables,\nsymboles d'observations astrales et de d�couvertes cosmiques.\n\n");

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