#pragma once
#include <iostream>
#include "qobject.h"
#include <string>
#include "qdebug.h"



class Caisse : public QObject 
{
	Q_OBJECT;

	
public:
	// le constructeur de la classe (un nouveau element ne peut pas contenir des article
	Caisse() { totalAvantTaxe_ = 0; totalDesTaxes_ = 0; };

	// creation de la structure article 
	struct Article {
		std::string description = "";
		double prix = 0;
		bool taxable = 0;

		std::string formatage() {
			std::string result;
			if ((*this).taxable)
				result = description + "\t" + getPrix() + "\t taxable";
			else
				result = description + "\t" + getPrix();

			return result;
		}
		
		std::string floatConversionToString(float valeur)  {
			float rounded = std::round(valeur * std::pow(10, 2)) / std::pow(10, 2);
			std::string preResult = std::to_string(rounded);
			int pos = preResult.find(".");
			std::string result = preResult.substr(0, pos + 3);
			return result;
		}
		
		std::string getPrix() {
			return floatConversionToString(prix);
		}
	};

	//getter pour le total vant taxe
	double getTotalAvantTaxe() const { return totalAvantTaxe_; }
	
	// le vecteur pour les articles ajoutes
	std::vector <Article> articleAjoutes;

	// pour le bouton reinitialiser
	void reinitialiser() { articleAjoutes.clear();}

	// float to string (cette partie du code a ete copiee de stackOverflow)
	std::string floatConversionToString(float valeur) const {
		float rounded = std::round(valeur * std::pow(10, 2)) / std::pow(10, 2);
		std::string preResult = std::to_string(rounded);
		int pos = preResult.find(".");
		std::string result = preResult.substr(0, pos + 3);
		return result;
	}

	// getter pour le total avant taxe
	std::string getTotalAvTaxe() const {return floatConversionToString(totalAvantTaxe_); }
	
	//pour recalculer le total avant taxe
	void calculerTotalAvantTaxe();

	//getter pour le total des taxes
	std::string getTotalDesTaxes() const { return floatConversionToString(totalDesTaxes_);}

	//pour calculer le total des taxes
	void calculTotalDesTaxes();

	//getter pour la somme total
	std::string getTotal() { return floatConversionToString(totalAvantTaxe_ + totalDesTaxes_); }

public slots:
	void ajouterArticle(Article article);
	void retirerArticle(std::string description);

   signals:
	void articleAjoute();
	void articleRetire();

private:
	double totalAvantTaxe_;
	double totalDesTaxes_;
};