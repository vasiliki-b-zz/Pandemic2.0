#pragma once

#include <string>

namespace PawnColour {
	enum PawnColour {
		RED,
		YELLOW,
		BLUE,
		GREEN,
		ORANGE,
		PINK,
		PURPLE,
		NONE
	};

	//static const int SIZE = 7;
};

PawnColour::PawnColour PawnColourStringToEnum(std::string s);
std::string PawnColourEnumToString(PawnColour::PawnColour c);


