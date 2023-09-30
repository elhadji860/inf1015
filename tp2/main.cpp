#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

using namespace std;
using namespace iter;
using namespace gsl;

const string SEPARATION = "\n\033[35m════════════════════════════════════════\033[0m\n";

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
gsl::span<Designer*> spanListeDesigners(const ListeDesigners& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion

//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.
// Cette fonction renvoie le pointeur vers le designer si elle le trouve dans
// un des jeux de la ListeJeux. En cas contraire, elle renvoie un pointeur nul.

bool estDansLaListe(Designer designer, ListeJeux listeJeux) {
	bool result = false;

	for (int i = 0; i < listeJeux.nElements; ++i) {
		for (int j = 0; j < listeJeux.elements[i]->designers.nElements; ++j) {
			if ((*(listeJeux.elements[i]->designers.elements))[j].nom == designer.nom) {
				result = true;
			}
		}
	}

	return result;
}

Designer* trouverDesigner(ListeJeux listeJeux, Designer designer) {


	if (estDansLaListe(designer, listeJeux)) {
		return &designer;
	}
	else {
		return nullptr;
	}
}

Designer* lireDesigner(istream& fichier, ListeJeux listeJeuxPrincipale)
{
	Designer designer = {}; // On initialise une structure vide de type Designer.
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure designer sont remplis
	// avec la bonne information.
	//
	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
	// Attention, valider si le designer existe déjà avant de le créer, sinon
	// on va avoir des doublons car plusieurs jeux ont des designers en commun
	// dans le fichier binaire. Pour ce faire, cette fonction aura besoin de
	// la liste de jeux principale en paramètre.
	Designer* ptrDesigner = nullptr;
	if (!estDansLaListe(designer, listeJeuxPrincipale)) {
		ptrDesigner = new Designer;
		ptrDesigner->nom = designer.nom;
		ptrDesigner->anneeNaissance = designer.anneeNaissance;
		ptrDesigner->pays = designer.pays;
		ListeJeux* listeJeuxParticipe = new ListeJeux;
		(listeJeuxParticipe->elements) = new Jeu * [1];
		ptrDesigner->listeJeuxParticipes = *listeJeuxParticipe;
	}
	// Afficher un message lorsque l'allocation du designer est réussie.
	cout << "l'allocation du designer est réussie." << endl;
	cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return ptrDesigner; //TODO: Retourner le pointeur vers le designer crée.
}

//TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
// Cette fonction doit recevoir en paramètre la nouvelle capacité du nouveau
// tableau. Il faut allouer un nouveau tableau assez grand, copier ce qu'il y
// avait dans l'ancien, et éliminer l'ancien trop petit. N'oubliez pas, on copie
// des pointeurs de jeux. Il n'y a donc aucune nouvelle allocation de jeu ici !
void changementDeTaille(ListeJeux& listeJeux, int facteur) {
	Jeu** nouveauTableau;
	Jeu** element = listeJeux.elements;
	nouveauTableau = new Jeu* [(listeJeux.nElements) * facteur];

	for (int i = 0; i < listeJeux.nElements; ++i) {
		nouveauTableau[i] = element[i];
	}
	delete[] listeJeux.elements;
	listeJeux.elements = nouveauTableau;
}
//TODO: Fonction pour ajouter un Jeu à ListeJeux.
// Le jeu existant déjà en mémoire, on veut uniquement ajouter le pointeur vers
// le jeu existant. De plus, en cas de saturation du tableau elements, cette
// fonction doit doubler la taille du tableau elements de ListeJeux.
// Utilisez la fonction pour changer la taille du tableau écrite plus haut.
void ajouterJeux(Jeu* jeu, ListeJeux& listejeux) {
	if (listejeux.capacite != 0) {
		if (listejeux.capacite <= listejeux.nElements) {
			changementDeTaille(listejeux, 2);
			listejeux.capacite *= 2;
		}
		Jeu*& element = *(listejeux.elements);
		element[listejeux.nElements] = *jeu;
		listejeux.nElements += 1;
	}
	else {
		Jeu** elements = new Jeu * [1];
		elements[0] = jeu;
		listejeux.capacite += 1;
		listejeux.nElements += 1;
		listejeux.elements = elements;
	}
}
//TODO: Fonction qui enlève un jeu de ListeJeux.
// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le
// pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le
// jeu à être retiré par celui présent en fin de liste et décrémenter la taille
// de celle-ci.

void enleverJeu(Jeu* jeu, ListeJeux& listejeux) {
	Jeu**& element = (listejeux.elements);
	for (int i = 0; i < listejeux.nElements; ++i) {
		if (jeu == element[i]) {
			element[i] = element[listejeux.nElements - 1];
			listejeux.nElements -= 1;
		}
	}

}

Jeu* lireJeu(istream& fichier, ListeJeux listeJeuPrincipale)
{
	Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.

	//TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// Attention, il faut aussi créer un tableau dynamique pour les designers
	// que contient un jeu. Servez-vous de votre fonction d'ajout de jeu car la
	// liste de jeux participé est une ListeJeu. Afficher un message lorsque
	// l'allocation du jeu est réussie.

	Jeu* ptrJeu = new Jeu;
	ptrJeu = &jeu;

	ListeDesigners* listeDesigners = new ListeDesigners;
	listeDesigners->elements = new Designer * [jeu.designers.nElements];

	for ([[maybe_unused]] int i : iter::range(jeu.designers.nElements)) {


		(listeDesigners->elements)[i] = lireDesigner(fichier, listeJeuPrincipale);
		ajouterJeux(ptrJeu, ((listeDesigners->elements)[i])->listeJeuxParticipes);
		//TODO: Mettre le designer dans la liste des designer du jeu.




		//TODO: Ajouter le jeu à la liste des jeux auquel a participé le designer.

	}
	jeu.designers = *listeDesigners;
	cout << "allocatiomjeu terminer";
	return ptrJeu; //TODO: Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};
	for ([[maybe_unused]] int n : iter::range(nElements))
	{
		(listeJeux.elements)[n] = lireJeu(fichier, listeJeux); //TODO: Ajouter le jeu à la ListeJeux.
	}

	return listeJeux; //TODO: Renvoyer la ListeJeux.
}

//TODO: Fonction pour détruire un designer (libération de mémoire allouée).
// Lorsqu'on détruit un designer, on affiche son nom pour fins de débogage.
void detruireDesigner(Designer designer) {

	ListeJeux* ptrListe = &(designer.listeJeuxParticipes);
	delete ptrListe;

	Designer* ptrDesigner = &designer;
	delete ptrDesigner;

}
//TODO: Fonction qui détermine si un designer participe encore à un jeu.
bool estParticipant(Designer designer, Jeu jeu) {
	for (int i = 0; i < jeu.designers.nElements; ++i) {
		if ((jeu.designers.elements)[i]->nom == designer.nom) {
			return true;
		}
	}
	return false;
}
//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des designers (un jeu contenant
// une ListeDesigners). On doit commencer par enlever le jeu à détruire des jeux
// qu'un designer a participé (listeJeuxParticipes). Si le designer n'a plus de
// jeux présents dans sa liste de jeux participés, il faut le supprimer.  Pour
// fins de débogage, affichez le nom du jeu lors de sa destruction.
void detruireJeu(Jeu jeu) {
	for (int i = 0; i < jeu.designers.nElements; ++i) {
		if (estParticipant(*(jeu.designers.elements)[i], jeu)) {
			enleverJeu(&jeu, (jeu.designers.elements)[i]->listeJeuxParticipes);
			if (((jeu.designers.elements)[i])->listeJeuxParticipes.nElements == 0) {
				detruireDesigner(*(jeu.designers.elements)[i]);
			}
		}
	}
	delete[] & (jeu.designers);
	delete& jeu;
}
//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
void detruireListeJeux(ListeJeux listeJeu) {
	for (int i = 0; i < listeJeu.nElements; ++i) {
		detruireJeu(*(listeJeu.elements[i]));
	}
	delete[] & (listeJeu.elements);
	delete& listeJeu;
}
void afficherDesigner(const Designer& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
		<< endl;
}

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
// Servez-vous de la fonction afficherDesigner ci-dessus.
void afficherInfosJeu(Jeu jeu) {
	cout << "annee de sortie: " << jeu.anneeSortie << endl;
	cout << "titre: " << jeu.titre << endl;
	cout << "developpeur: " << jeu.developpeur << endl;
	cout << "designer: " << endl;
	for (int i = 0; i < jeu.designers.nElements; ++i) {
		afficherDesigner(*(jeu.designers.elements[i]));
	}
}
//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main.
void afficherJeux(ListeJeux listejeu) {
	for (int i = 0; i < listejeu.nElements; ++i) {
		afficherInfosJeu(*(listejeu.elements[i]));
		cout << SEPARATION << endl;
	}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux listePrincipale = creerListeJeux("C:\\Users\\elhad\\OneDrive\\Attachments\\Bureau\\New folder (2)\\jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.

	cout << ligneSeparation << endl;

	//TODO: Appel à votre fonction d'affichage de votre liste de jeux.
	afficherJeux(listePrincipale);
	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	detruireListeJeux(listePrincipale);
	return 0;
}
