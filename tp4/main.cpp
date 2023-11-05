/**
* Programme qui exploite un fichier de Heros et un fichier de vilains.
* \file   main.cpp
* \author Sarr et Diaw
* \date   05 Novembre 2023
* Créé le 31 octobre 2023
*/

#pragma once
#include <fstream>
#include <iostream>
#include "bibliotheque_cours.hpp"
#include <string>
#include <memory>
#include <functional>
#include "Vilain.hpp"
#include "Hero.hpp"
#include "Personnage.hpp"
#include "Hero.hpp"
#include <vector>
#include <string>
#include "VilainHeros.hpp"

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(std::istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(std::istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

std::string lireString(std::istream& fichier)
{
	std::string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), std::streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

using namespace std;

const string CHEMIN_FICHIER_HEROS = "C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\tp4\\heros.bin";
const string CHEMIN_FICHIER_VILAINS = "C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\tp4\\vilains.bin";

Heros lireHeros(istream& fichier) {
	string nom = lireString(fichier);
	string parution = lireString(fichier);
	string ennemie = lireString(fichier);
	int nbAllies = lireUint8(fichier);
	vector<string> allies;
	for (int i = 0; i < nbAllies; ++i) {
		allies.push_back(lireString(fichier));
	}
	Heros Heros(nom, parution, ennemie, allies);
	return Heros;
}

Vilain lireVilain(istream& fichier) {
	string nom = lireString(fichier);
	string parution = lireString(fichier);
	string objectif = lireString(fichier);
	Vilain vilain(nom, parution, objectif);
	return vilain;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	// Ouverture des fichiers binaires
	ifstream fichierHeros(CHEMIN_FICHIER_HEROS, ios::binary);
	ifstream fichierVilains(CHEMIN_FICHIER_VILAINS, ios::binary);
	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	//TODO: Votre code pour le main commence ici
	vector<Heros> heros;
	vector <Vilain> vilains;
	vector<Personnage*> personnages;

	// lecture nombre heros et nombre vilains
	int nbHeros = lireUint16(fichierHeros);
	int nbVilains = lireUint16(fichierVilains);

	// ajout dans les vectors
	for (int i = 0; i < nbHeros; ++i) {
		heros.push_back(lireHeros(fichierHeros));
	}
	for (int i = 0; i < nbVilains; ++i) {
		vilains.push_back(lireVilain(fichierVilains));
	}
	
	//affichage
	for (const auto& x : heros) {
		x.changerCouleur(cout, Palettes::PALETTE_4);
		x.afficher(cout);
	}
	cout << "\033[0m" << trait << endl;
	for (const auto& x : vilains) {
		x.changerCouleur(cout, Palettes::PALETTE_4);
		x.afficher(cout);
	}

	//ajout dans personnages
	for ( auto& x : heros) {
		personnages.push_back(&x);
	}
	for ( auto& x : vilains) {
		personnages.push_back(&x);
	}

	//affichage personnages
	cout << "\033[0m" << trait << endl;
	for (auto& x : personnages) {
		x->changerCouleur(cout, Palettes::PALETTE_2);
		x->afficher(cout);
	}
	

	//partie vilainHeros
	cout << "\033[0m" << trait << endl;
	VilainHeros vilainHeros(heros[0], vilains[1]);
	personnages.push_back(&vilainHeros);
	personnages[nbHeros + nbVilains]->changerCouleur(cout, Palettes::PALETTE_2);
	personnages[nbHeros + nbVilains]->afficher(cout);

	//fin
	cout << "\033[0m" << trait << endl;
}
