#include "CityVertex.h"

//CityVertex::CityVertex(City city) : city(city), Vertex(city.getName(), city.getColour())
//{
//	this->city = city;
//	this->diseaseCubes = 0;
//	this->researchStations = 0;
//}

CityVertex::~CityVertex()
{
}

void CityVertex::removeDiseaseCubes(int number)
{
	if (diseaseCubes == 0)
		return;
	else if (diseaseCubes - number < 0)
		removeAllDiseaseCubes();
	else
		diseaseCubes -= number;
}

void CityVertex::addDiseaseCubes(int number) {
	if(diseaseCubes + number > 4) {
		this->diseaseCubes = 4;
	} else {
		this->diseaseCubes = number;
	}
}

std::string CityVertex::toString()
{
	std::string s = "";
	s += getName() +"(" + DiseaseColourEnumToString(city.getColour()) + "," + std::to_string(this->getDiseaseCubes()) + "," + std::to_string(this->hasResearchStation()) + ")";
	return s;
}


