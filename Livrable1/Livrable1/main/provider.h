#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <map>

enum class Action {DEPLACEMENT, INFORMATION};
enum class Coordonnee {NORD, SUD, EST, OUEST};
enum class Etat { AFFICHAGE, PRISE_INFORMATION };

struct GroupeCommande
{
	Action nom;
	std::vector<std::string> commandes;
};