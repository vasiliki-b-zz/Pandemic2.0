#include "PawnColour.h"

PawnColour::PawnColour PawnColourStringToEnum(std::string s)
{
	PawnColour::PawnColour colour;

	if (s == "RED")
		colour = PawnColour::RED;
	else if (s == "YELLOW")
		colour = PawnColour::YELLOW;
	else if (s == "BLUE")
		colour = PawnColour::BLUE;
	else if (s == "GREEN")
		colour = PawnColour::GREEN;
	else if (s == "ORANGE")
		colour = PawnColour::ORANGE;
	else if (s == "PINK")
		colour = PawnColour::PINK;
	else if (s == "PURPLE")
		colour = PawnColour::PURPLE;
	else
		colour = PawnColour::NONE;

	return colour;
}

std::string PawnColourEnumToString(PawnColour::PawnColour c)
{
	std::string colour;

	switch (c)
	{
	case PawnColour::RED:
		colour = "RED";
		break;
	case PawnColour::YELLOW:
		colour = "YELLOW";
		break;
	case PawnColour::BLUE:
		colour = "BLUE";
		break;
	case PawnColour::GREEN:
		colour = "GREEN";
		break;
	case PawnColour::ORANGE:
		colour = "ORANGE";
		break;
	case PawnColour::PINK:
		colour = "PINK";
		break;
	case PawnColour::PURPLE:
		colour = "PURPLE";
		break;
	default:
		colour = "NONE";
		break;
	}

	return colour;
}
