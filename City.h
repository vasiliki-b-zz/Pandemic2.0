#pragma once

#include <string>
#include "DiseaseColour.h"

class City
{
public:
	//City();
	City(std::string name, Disease::Colour colour) { this->name = name; this->colour = colour; };
	~City();
	std::string getName() const { return name; };
	Disease::Colour getColour() const { return colour; };
	std::string toString();

private:
	std::string name;
	Disease::Colour colour;
};

