#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <utility>
#include<algorithm>

enum class Action { DEPLACEMENT, INFORMATION, USE_OBJET, INFORMATION_OBJET, USE};
enum class Coordonnee { NORD, SUD, EST, OUEST };
enum class Etat { AFFICHAGE, PRISE_INFORMATION};
enum class ActionsObjet { RIEN, LUMIERE, DEBLOQUE_SALLE};


struct GroupeCommande
{
	Action nom;
	std::vector<std::string> commandes;
};

