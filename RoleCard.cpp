#include "RoleCard.h"
#include <sstream>

RoleCard::~RoleCard()
{
}

std::string RoleCard::print()
{
	std::istringstream in_stream(Card::getDescription());
	std::string line;

	std::string s = "";
	s += "\t~ " + CardTypeEnumToString(Card::getType()) + " CARD ~\n"
		+ "\t" + Card::getName() + " ("
		+ PawnColourEnumToString(colour) + " Pawn):\n\n";

	while (std::getline(in_stream, line, '\\'))
	{
		s += "\to   " + line + "\n";
	}
	return s;
}

std::string RoleCard::toString()
{
	std::string s = "";
	s += Card::getName() + "(" + PawnColourEnumToString(colour) + ") " + " : " + Card::getDescription();
	return s;
}

std::string RoleCard::toStringSave()
{
	std::string s = "";
	s += Card::getName() + ";" + PawnColourEnumToString(colour) + ";" + Card::getDescription();
	return s;
}
