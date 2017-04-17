#include "CardType.h"

CardType::CardType CardTypeStringToEnum(std::string s)
{
	CardType::CardType type;

	if (s == "INFECTION")
		type = CardType::INFECTION;
	else if (s == "CITY")
		type = CardType::CITY;
	else if (s == "ROLE")
		type = CardType::ROLE;
	else if (s == "REFERENCE")
		type = CardType::REFERENCE;
	else if (s == "EVENT")
		type = CardType::EVENT;
	else if (s == "EPIDEMIC")
		type = CardType::EPIDEMIC;
	else
		type = CardType::NONE;

	return type;
}

std::string CardTypeEnumToString(CardType::CardType t)
{
	std::string type;

	switch (t)
	{
	case CardType::INFECTION:
		type = "INFECTION";
		break;
	case CardType::CITY:
		type = "CITY";
		break;
	case CardType::ROLE:
		type = "ROLE";
		break;
	case CardType::REFERENCE:
		type = "REFERENCE";
		break;
	case CardType::EVENT:
		type = "EVENT";
		break;
	case CardType::EPIDEMIC:
		type = "EPIDEMIC";
		break;
	default:
		type = "NONE";
		break;
	}

	return type;
}

