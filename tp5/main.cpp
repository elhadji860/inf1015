#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include <map>
using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

const string CHEMIN_HEROS = "C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\tp5\\heros.bin";
const string CHEMIN_VILAINS = "C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\inf1015\\tp5\\vilains.bin";

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
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

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>(CHEMIN_HEROS);
	vector<Vilain> vilains = lireFichier<Vilain>(CHEMIN_VILAINS);
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto& h : heros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto& v : vilains) {
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto& p : peronnages) {
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout,1);
	kefkaCrono.afficher(cout);
	#endif
	//}

	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeHeros;
	for (auto x : heros)
		listeHeros.push_back(x);

	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	ListeLiee<Heros>::iterator  iter1(trouverParNom(listeHeros, "Alucard"));

	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	cout << separateurSections << "heros retrouve:" << endl;
	for (ListeLiee<Heros>::iterator x (iter1); x != (listeHeros.end()); x.avancer()) {
		if ((*x).getNom() == "Aya Brea")
			iter1 = x;
	}

	(*iter1).afficher(cout);

	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	cout << separateurSections << "heros ajoute:" << endl;
	Heros  Arthur("Arthur Morgan", "Red Dead Redemption 2", "Micah Bell");
	vector<string> allies = { "John Marston", "Charles", "Sean", "Abigail Roberts" };
	for (auto x : allies)
		Arthur.ajouterAllie(x);

	ListeLiee<Heros>::iterator  iter2 = listeHeros.insert(iter1,Arthur);
	(*iter2).changerCouleur(cout, 2);
	(*iter2).afficher(cout);

	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	(*listeHeros.begin()).afficher(cout);
	cout << separateurSections << "ancienne taille : " << listeHeros.size()<< endl;
	for (ListeLiee<Heros>::iterator x = iter2; x != listeHeros.begin(); x.reculer()) {
		if ((*x).getNom() == "Mario") {
			x = listeHeros.erase(x);
			
			cout << "hero suivant:" << endl;
			(*x).changerCouleur(cout, 3);
			(*x).afficher(cout);

			cout << "nouvelle taille : " << listeHeros.size();
		}
	}
	//TODO: Effacez le premier élément de la liste.
	cout << separateurSections << "afficher premier element" << endl;
	ListeLiee<Heros>::iterator headIter = listeHeros.begin();
	headIter = listeHeros.erase(headIter);
	(*(headIter)).afficher(cout);

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...
	cout << separateurSections << "second affichage:"<< endl;
	for (ListeLiee<Heros>::iterator x = listeHeros.begin(); x != listeHeros.end(); x.avancer())
		(*x).afficher(cout);

	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << separateurSections << "troisieme affichage:" << endl;
	for (auto x : listeHeros)
		x.afficher(cout);

	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).

	cout << separateurSections << "affichage ordre alphabetique:" << endl;
	map<string, Heros> mapHeros;
	for (auto x : heros)
		mapHeros.insert({ x.getNom(), x });

	for (auto [x, y] : mapHeros)
		y.afficher(cout);

	//Reponse a la question :
	// la recherche dans le conteneur est O(logn) alors que la recherche dans la liste Liee est O(n) par consequent
	// la recherche dams le conteneur est plus rapide

	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
}
