#include "Caisse.h"
#include <algorithm>
#include <vector>
#include <numeric>
#include <exception>
#include "InvalidValueException.h"


void Caisse::ajouterArticle(Article* article) 
{
	std::string valeurTestExcept = article->description;
	remove(valeurTestExcept.begin(), valeurTestExcept.end(), ' ');

	if (valeurTestExcept == "" || article->prix == 0)
		throw InvalidValueException("mauvaise valeur pour le prix ou la description");
	articleAjoutes.push_back(article);
	emit articleAjoute();
}

void Caisse::retirerArticle(Article* aRetirer)
{
	auto it = std::remove_if(articleAjoutes.begin(), articleAjoutes.end(), [=](Article* article) {return aRetirer == article; });
	

	articleAjoutes.erase(it);

	delete aRetirer;

	emit articleRetire();

}

void Caisse::calculerTotalAvantTaxe()
{
	totalAvantTaxe_ = std::accumulate(articleAjoutes.begin(), articleAjoutes.end(), 0, [](double a, Article* b) {return a + b->prix; });
}

void Caisse::calculTotalDesTaxes()
{
	std::vector<Article*> produitTaxable;
	std::copy_if(articleAjoutes.begin(), articleAjoutes.end(), std::back_inserter(produitTaxable), [](Article* a) {return a->taxable; });
	totalDesTaxes_ = (std::accumulate(produitTaxable.begin(), produitTaxable.end(), 0, [](double a, Article* b) {return a + b->prix; }))*(14.975/100);
}
