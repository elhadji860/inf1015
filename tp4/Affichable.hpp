#pragma once
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include <string>
enum class Palettes { PALETTE_1, PALETTE_2, PALETTE_3, PALETTE_4, PALETTE_5, RESET };

class Affichable 
{
public:
	virtual std::ostream& afficher(std::ostream& os) const = 0;
	virtual std::ostream& changerCouleur(std::ostream& os, Palettes palette) const  = 0;
	virtual ~Affichable() = default;

};