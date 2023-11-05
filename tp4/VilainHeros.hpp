#pragma once
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include "Vilain.hpp"
#include "Hero.hpp"
#include "Personnage.hpp"
#include "Hero.hpp"
#include <vector>
#include <string>

class VilainHeros :  public Heros,  public Vilain {
public:
	VilainHeros(const Heros& heros, const Vilain& vilain) :
		Personnage(heros.Personnage::getNom()+ vilain.Personnage::getNom(), heros.Personnage::getParution() + "-" + vilain.Personnage::getParution()),
		Heros(heros.Personnage::getNom(),heros.Personnage::getParution(), heros.getEnnemie(),heros.getAllies()), Vilain(vilain.Personnage::getNom(),vilain.Personnage::getParution(),vilain.getObjectif() ),
		missionSpeciale_(vilain.getObjectif()+" dans le monde de " + heros.Personnage::getParution()) {}

	std::ostream& afficher(std::ostream& os) const override {
		Personnage::afficher(os);
		os << Vilain::getObjectif() << std::endl;
		os<<"Allies : "<<std::endl;
		for (auto& x : Heros::getAllies()) {
			os << "\t" << x << std::endl; 
		}
		os << "Mission speciale : " << missionSpeciale_ << "\n" << std::endl;
		
		return os;
	}
	std::ostream& changerCouleur(std::ostream& os, Palettes palette) const override {
		switch (palette)
		{
		case Palettes::PALETTE_1:
			os << "\033[32m";
			break;
		case Palettes::PALETTE_2:
			os << "\033[96m";
			break;
		case Palettes::PALETTE_3:
			os << "\033[35m";
			break;
		case Palettes::PALETTE_4:
			os << "\033[34m";
			break;
		case Palettes::PALETTE_5:
			os << "\033[91m";
			break;
		case Palettes::RESET:
			os << "\033[0m";
			break;
		default:
			break;
		}
		return os;
	}
private:
	std::string missionSpeciale_;
};