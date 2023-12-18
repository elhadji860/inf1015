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
		bibliotheque_ = make_shared<Piece>("bibliotheque", true, false);
		laboratoire_ = make_shared<Piece>("laboratoire", true, false);
		salleSecrete_ = make_shared<Piece>("salle secrete (elle se trouve a l'ouest de la salle de classe)", false, true);

		entree_->setVoisin(sallePrincipale_, AUCUNE, AUCUNE, AUCUNE);
		sallePrincipale_->setVoisin(bibliotheque_, entree_, laboratoire_, salleDeClasse_);
		salleDeClasse_->setVoisin(AUCUNE, AUCUNE, sallePrincipale_, salleSecrete_);
		bibliotheque_->setVoisin(AUCUNE, sallePrincipale_, AUCUNE, AUCUNE);
		laboratoire_->setVoisin(AUCUNE, AUCUNE, AUCUNE, sallePrincipale_);
		salleSecrete_->setVoisin(AUCUNE, AUCUNE, salleDeClasse_, AUCUNE);
		

		laboratoire_->setDescription("Un laboratoire lugubre eclaire par une lueur fantomatique,ou des etageres croulent sous le poids de fioles mysterieuses. \nL'air est impregne de magie ancienne,et un autel obscur au centre de la piece emet un murmure sinistre, \nevoquant des experiences interdites.\n\n");
		entree_->setDescription("Une salle d'entree majestueuse s'ouvre devant vous, \nles murs de pierre ornes de torches vacillantes. \nUn tapis rouge delave s'etend jusqu'a une porte massive, \nrevelant des fresques anciennes et des statues imposantes qui encadrent l'entree du donjon, \nevoquant une atmosphere de mystere et d'aventure.\n\n");
		salleDeClasse_->setDescription("Dans la salle de classe, \ndes pupitres soigneusement alignes remplissent l'espace, \neclaires par la lueur douce de lanternes magiques suspendues au plafond voute. \nAu tableau noir, des schemas magiques s'animent lentement tandis que des parchemins detailles et des grimoires s'alignent sur les etageres, \ncreant une atmosphere propice a l'apprentissage des arts mystiques.\n\n");
		sallePrincipale_->setDescription("Au coeur du hall principal,\nd'imposantes colonnes de marbre encadrent une entree majestueuse,\nlaissant filtrer la lueur doree des lustres suspendus au plafond voute.\nDes tapis luxueux recouvrent le sol poli,\nmenant a un trone ancestral sur une estrade ornee de motifs complexes,\nevoquant la grandeur d'un passe glorieux.\n\n");
		bibliotheque_->setDescription("Dans la bibliotheque, \nles etageres en bois sombre s'elevent jusqu'au plafond, \nchargees de tomes anciens et de parchemins soigneusement alignes.\nLa lueur douce de chandeliers antiques eclaire des fauteuils rembourres et des tables de lecture, \ninvitant a l'etude et a la contemplation silencieuse.\n\n");
		salleSecrete_->setDescription("salle secrete pour aucune raison apparante\n\n");

		auto becher = make_shared<Objet>("becher", " Recipient de laboratoire, en verre ou en plastique, dote d'un fond plat, d'un bec verseur et de graduations, utilise pour mesurer, melanger et chauffer des liquides en milieu experimental.\n\n", "vous l'examinez pour en apprendre plus\n");
		becher->setMotCle({ "becher" });
		laboratoire_->setObjets({becher});

		auto tapis = make_shared<Objet>("tapis", "surface souple et epaisse, souvent en tissu, utilisee pour couvrir le sol, ajouter du confort et decorer l'espace intérieur.\n\n", "vous essuyer vos chaussure avant d'entrer\n");
		tapis->setMotCle({ "tapis" });
		entree_->setObjets({ tapis });

		auto bouton = make_shared<ObjetCle>("bouton rouge", "un grand bouton rouge au fond de la salle\n\n", "vous appuyez dessus et entendez un grincement bizzare\n");
		bouton->setMotCle({ "bouton" });
		salleDeClasse_->setSalleDeb({ salleSecrete_ });
		salleDeClasse_->setObjets({ bouton });

		auto interrupteur = make_shared<ObjetLumiere>("interrupteur", "un interrupteur au fond de la salle\n\n", "**SWITCH**\n");
		auto chandelier = make_shared<Objet>("chandelier", "chandelier imposant accroche sur plafond\n\n", "vous ne pouvez pas l'atteindre\n");
		interrupteur->setMotCle({ "interrupteur" });
		chandelier->setMotCle({ "chandelier" });
		sallePrincipale_->setLienEclair({ bibliotheque_,laboratoire_ });
		sallePrincipale_->setObjets({ interrupteur, chandelier });

		auto livre = make_shared<Objet>("livre d'alchimie", "des formules, des formules et des formules\n\n", "vous essayer de lire mais vous ne comprennez pas grand chose\n");
		livre->setMotCle({ "livre" });
		bibliotheque_->setObjets({ livre });



		nom = "poly fantastique";
		personnagePrincipale_ = make_shared<Personnage>(entree_->getNom(), "heros");
		lieuxEvenements_ = entree_;
		actionPermises = { Action::DEPLACEMENT, Action::INFORMATION, Action::USE };


	};
	//definition de setters


	//definition de getters
	shared_ptr<Piece> getLieuxEvent() const { return lieuxEvenements_; }

	//fonctions pour les interactions
	string script;
	bool writing = false;
	bool commandeUnitaire = false;
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
			result = ("vers l'" +stringCoordonnee+" \n \n\033[93m ***" + lieuxEvenements_->getNom() + " ***\033[0m\n" + lieuxEvenements_->getDescription());
			if (lieuxEvenements_->getEclair())
			{
				if (lieuxEvenements_->getObjetsPresent().size())
				{
					result += "vous remarquez :\n";
					for (auto x : lieuxEvenements_->getObjetsPresent())
					{
						result += "	un(e) " + x->getNom() + '\n';
					}
					result += '\n';
					actionPermises = { Action::DEPLACEMENT, Action::INFORMATION, Action::USE };
				}
				else
				{
					actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
				}
			}
			else
			{
				result += "la piece est sombre vous ne distinguez rien\n\n";
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
			}
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
				script = "\n\033[93m***" + lieuxEvenements_->getNom() + "***\033[0m\n" + lieuxEvenements_->getDescription();
				writing = true;
			}
			else
			{
				if (lieuxEvenements_->getEclair())
				{
					actionPermises = { Action::INFORMATION_OBJET };
					writing = true;
				}
				else
				{
					script = "cette commande n'est pas permise";
					writing = true;
				}
			}
		}
		if (commande == "use")
		{
			if (commandeUnitaire)
			{
				script = "il manque un argument\n\n";
				writing = true;
			}
			else
			{
				actionPermises = { Action::USE_OBJET };
				writing = true;
			}
		}
	}
	void executionComplement(shared_ptr<Objet> ptrObjet)
	{
		if (actionPermises[0]==Action::INFORMATION_OBJET)
		{
			script = ptrObjet->getDescription();
			writing = true;
			actionPermises = { Action::DEPLACEMENT, Action::INFORMATION, Action::USE };
		}
		else if (actionPermises[0]==Action::USE_OBJET)
		{
			auto p = ptrObjet->use();
			script = p.second ;
			script += lieuxEvenements_->useRetroAction(p.first) + '\n';
			writing = true;
			if (lieuxEvenements_->getEclair())
			{
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION, Action::USE };
			}
			else
			{
				actionPermises = { Action::DEPLACEMENT, Action::INFORMATION };
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
	shared_ptr<Piece> salleSecrete_;

	shared_ptr<Personnage> personnagePrincipale_;

	shared_ptr<Piece> lieuxEvenements_;

	string nom;

	


};