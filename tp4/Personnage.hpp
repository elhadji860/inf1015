#pragma once
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include "Affichable.hpp"

class Personnage : public Affichable {
public:
	Personnage(std::string nom, std::string::parution): nom_(nom), parution_(parution){}

	std::ostream& afficher(std::ostream& os) const override {
		os << "Nom : " << nom_ << std::endl;
		os << "Parution : " << parution_ << std::endl;
		os << "  " << std::endl;
		return os;

	}
	std::ofstream& changerCouleur(std::ostream& os, Palettes palette) const {
		switch (palette)
		{
		case Palettes::PALETTE_1:
			os << "\033[103m";
			break;
		case Palettes::PALETTE_2:
			os << "\033[106m";
			break;
		case Palettes::PALETTE_3:
			os << "\033[105m";
			break;
		case Palettes::PALETTE_4:
			os << "\033[32m";
			break;
		case Palettes::PAlETTE_5:
			os << "\033[34m";
			break;
		case Palettes::RESET:
			os << "\033[0m";
			break;
		}
		return os;
	}
private:
	std::string nom_;
	std::string parution_

};