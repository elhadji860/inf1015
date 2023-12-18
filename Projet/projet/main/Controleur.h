#pragma once
#include "Monde.h"

using namespace std;

class Controleur
{
public:
	Controleur(shared_ptr<Monde> monde) : monde_(monde)
	{
		groupeCommandes_.push_back({ Action::DEPLACEMENT, {"n","s", "e", "o"} });
		groupeCommandes_.push_back({ Action::INFORMATION,{"look"} });
		groupeCommandes_.push_back({ Action::USE,{"use"} });
		actionPermises = monde_->actionPermises;

	};

	//definition de setters
	void setMonde(shared_ptr<Monde> monde) { monde_ = monde; }

	//fonctions pour le interaction
	string script;
	bool writing = false;
	void gestionCommande(string commande)
	{
		writing = false;
		script = "";
		actionPermises = monde_->actionPermises;
		
		if(actionPermises[0]== Action::INFORMATION_OBJET||actionPermises[0] == Action::USE_OBJET)
		{
			gestionComplement(commande);
		}

		else if (estValide(commande))
		{
			monde_->executionCommandeSimple(commande);
			
		}
		else
		{
			script = ("cette commande n'est pas permise \n\n");
			writing = true;
		}

	}
	bool estValide(string commande)
	{
		for (auto x : actionPermises)
		{
			for (auto y : groupeCommandes_)
			{
				if (y.nom == x)
				{
					for (auto z : y.commandes)
					{
						if (z == commande)
							return true;
					}
				}
			}
		}

		return false;
	}

	void gestionComplement(string commande)
	{
		auto p = complementEstValide(commande);
		if (p.first)
		{
			monde_->executionComplement(p.second);
			actionPermises = monde_->actionPermises;
		}
		else
		{
			script = ("cet argument n'est pas permis \n\n");
			writing = true;
			monde_->actionPermises = { Action::DEPLACEMENT, Action::INFORMATION, Action::USE };
		}
	}
	pair<bool, shared_ptr<Objet>> complementEstValide(string commande)
	{
		for (auto x : monde_->getLieuxEvent()->getObjetsPresent())
		{
			for (auto y : x->getMotCle())
			{
				if (commande.find(y)!=string::npos)
				{
					return { true, x };
				}
			}
		}
		return { false,nullptr };
	}

private:
	shared_ptr<Monde> monde_;
	vector<GroupeCommande>groupeCommandes_;
	vector<Action> actionPermises;
};
