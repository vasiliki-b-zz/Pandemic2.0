#include <sstream>
#include "Card.h"

Card::~Card()
{
}

std::string Card::print()
{
	std::istringstream in_stream(getDescription());
	std::string line;

	std::string s = "";
	s += "\t~ " + CardTypeEnumToString(Card::getType())
		+ " CARD ~\n" + "\t" + Card::getName() + ":\n\n";

	while (std::getline(in_stream, line, '\\'))
	{
		s += "\to   " + line + "\n";
	}
	return s;
}

std::string Card::toString()
{
	std::string s = "";
	s += name + " : " + description;
	return s;
}

std::string Card::getCard() {
	std::string s = "";
	s+= name + "," + description + "," + CardTypeEnumToString(type);
	return s;
}
