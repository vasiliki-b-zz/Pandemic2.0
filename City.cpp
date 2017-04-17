#include "City.h"



//City::City()
//{
//}


City::~City()
{
}

std::string City::toString()
{
	std::string s = "";
	s = name + "(" + DiseaseColourEnumToString(colour) + ")";
	return s;
}
