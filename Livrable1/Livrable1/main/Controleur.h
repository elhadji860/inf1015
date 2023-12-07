#pragma once
#include "Monde.h"

using namespace std;

class Controleur
{
public:
	Controleur(shared_ptr<Monde> monde ) : monde_(monde)
	{
		groupeCommandes_.push_back({ Action::DEPLACEMENT, {"n","s", "e", "o"} });
		groupeCommandes_.push_back({ Action::INFORMATION,{"look"} });

	};

	//definition de setters
	void setMonde(shared_ptr<Monde> monde) { monde_ = monde; }

	//fonctions pour le interaction
	string script;
	bool writing = false;
	void gestionCommande(string commande, vector<Action> actionPermises)
	{
		writing = false;
		script = "";

		if (estValide(commande, actionPermises))
		{
			monde_->execution(commande);
		}
		else
		{
			script =  ("cette commande n'est pas permise \n\n");
			writing = true;
		}

	}
	bool estValide(string commande, vector<Action> actionPermises)
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

private:
	shared_ptr<Monde> monde_;
	vector<GroupeCommande>groupeCommandes_;
};