#pragma once

#include <string>

namespace Disease {
	enum Colour {
		BLUE,
		YELLOW,
		BLACK,
		RED,
		NONE
	};
};

Disease::Colour DiseaseColourStringToEnum(std::string s);
std::string DiseaseColourEnumToString(Disease::Colour c);
