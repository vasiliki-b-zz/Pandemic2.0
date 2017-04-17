#pragma once

#include <string>

namespace CardType {
	enum CardType {
		INFECTION,
		CITY,
		ROLE,
		REFERENCE,
		EVENT,
		EPIDEMIC,
		NONE
	};
};

CardType::CardType CardTypeStringToEnum(std::string s);
std::string CardTypeEnumToString(CardType::CardType c);