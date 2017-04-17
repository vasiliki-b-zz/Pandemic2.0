#include "DiseaseColour.h"

Disease::Colour DiseaseColourStringToEnum(std::string s)
{
	Disease::Colour colour;

	if (s == "RED")
		colour = Disease::RED;
	else if (s == "YELLOW")
		colour = Disease::YELLOW;
	else if (s == "BLACK")
		colour = Disease::BLACK;
	else if (s == "BLUE")
		colour = Disease::BLUE;
	else
		colour = Disease::NONE;

	return colour;
}

std::string DiseaseColourEnumToString(Disease::Colour c)
{
	std::string colour;

	switch (c)
	{
	case Disease::RED:
		colour = "RED";
		break;
	case Disease::YELLOW:
		colour = "YELLOW";
		break;
	case Disease::BLACK:
		colour = "BLACK";
		break;
	case Disease::BLUE:
		colour = "BLUE";
		break;
	default:
		colour = "NONE";
		break;
	}

	return colour;
}

