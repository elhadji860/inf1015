#pragma once
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include "Personnage.hpp"
#include <vector>
#include <string>

class Vilain : virtual public Personnage {
public:
	Vilain(std::string nom, std::string parution, std::string objectif ) : Personnage(nom,parution), objectif_(objectif){}

	 std::ostream& afficher(std::ostream& os) const override {
		Personnage::afficher(os);
		os << "objectif : " << objectif_ << std::endl;
		os << " " << std::endl;
		return os;
	}

	 std::ostream& changerCouleur(std::ostream& os, Palettes palette) const override {
		switch (palette)
		{
		case Palettes::PALETTE_1:
			os << "\033[34m";
			break;
		case Palettes::PALETTE_2:
			os << "\033[95m";
			break;
		case Palettes::PALETTE_3:
			os << "\033[96m";
			break;
		case Palettes::PALETTE_4:
			os << "\033[91m";
			break;
		case Palettes::PALETTE_5:
			os << "\033[34m";
			break;
		case Palettes::RESET:
			os << "\033[0m";
			break;
		default:
			break;
		}
		return os;
	}
	std::string getObjectif() const { return objectif_; }
private:
	std::string objectif_;
};