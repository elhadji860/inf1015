#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <utility>
#include <optional>
#include<algorithm>

enum class Action { DEPLACEMENT, INFORMATION, USE_OBJET, INFORMATION_OBJET};
enum class Coordonnee { NORD, SUD, EST, OUEST };
enum class Etat { AFFICHAGE, PRISE_INFORMATION};
enum class ActionsObjet { RIEN, LUMIERE, DEBLOQUE_SALLE};


struct GroupeCommande
{
	Action nom;
	std::vector<std::string> commandes;
};

bool estDansString(std::string string1, std::string string2);