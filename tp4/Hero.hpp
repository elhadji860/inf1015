#pragma once
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include "Personnage.hpp"
#include <vector>
#include <string>

class Heros : virtual public Personnage {
public:
	Heros(std::string nom, std::string parution,std::string ennemie, std::vector < std::string > allies ) : Personnage(nom, parution), ennemie_(ennemie), allies_(allies){}

	std::ostream& afficher(std::ostream& os) const override {
		Personnage::afficher(os);
		os << "Ennemie : " << ennemie_ << std::endl;
		os << "allies : " << std::endl;
		for (auto& x : allies_) {
			os << "\t" << x << std:: endl;
		}
		os << " " << std::endl;
		return os;
	}

	std::ostream& changerCouleur(std::ostream& os, Palettes palette) const override{
		switch (palette)
		{
		case Palettes::PALETTE_1:
			os << "\033[96m";
			break;
		case Palettes::PALETTE_2:
			os << "\033[34m";
			break;
		case Palettes::PALETTE_3:
			os << "\033[91m";
			break;
		case Palettes::PALETTE_4:
			os << "\033[93m";
			break;
		case Palettes::PALETTE_5:
			os << "\033[32m";
			break;
		case Palettes::RESET:
			os << "\033[0m";
			break;
		default:
			break;
		}
		return os;
	}
	std::vector<std::string> getAllies() const { return allies_; }
	std::string getEnnemie() const { return ennemie_; }
private:
	std::vector<std::string> allies_;
	std::string ennemie_;
};