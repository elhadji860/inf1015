#include "Caisse.h"
#include <algorithm>
#include <vector>
#include <numeric>


void Caisse::ajouterArticle(Article article) {
	articleAjoutes.push_back(article);
	emit articleAjoute();
}

void Caisse::retirerArticle(std::string description)
{
	auto it = std::remove_if(articleAjoutes.begin(), articleAjoutes.end(), [=](Article article) {return article.description == description; });
	
	std::vector<Article*> toDeallocate;
	
	articleAjoutes.erase(it, articleAjoutes.end());

	emit articleRetire();

}

void Caisse::calculerTotalAvantTaxe() {
	totalAvantTaxe_ = std::accumulate(articleAjoutes.begin(), articleAjoutes.end(), 0, [](double a, Article b) {return a + b.prix; });
}

void Caisse::calculTotalDesTaxes() {
	std::vector<Article> produitTaxable;
	std::copy_if(articleAjoutes.begin(), articleAjoutes.end(), std::back_inserter(produitTaxable), [](Article a) {return a.taxable; });
	totalDesTaxes_ = (std::accumulate(produitTaxable.begin(), produitTaxable.end(), 0, [](double a, Article b) {return a + b.prix; }))*(14.975/100);
}
