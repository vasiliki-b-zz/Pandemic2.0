#pragma once

#include "City.h"
#include "Vertex.h"

class CityVertex : public Vertex
{
public:
	CityVertex(City city) : city(city), Vertex(city.getName(), city.getColour()) { city = city; diseaseCubes = 0; researchStation = false; };
	~CityVertex();
	City getCity() { return city; };
	//void setCity() { this->city = city; };
	Disease::Colour getColour() const { return city.getColour(); };
	int getDiseaseCubes() { return this->diseaseCubes; };
	void addDiseaseCubes(int number);
//	void addDiseaseCube() { diseaseCubes++; };
	void removeDiseaseCubes(int number);
	void removeAllDiseaseCubes() { diseaseCubes = 0; };
	bool hasResearchStation() { return this->researchStation; };
	void addResearchStation() { researchStation = true; };
	void removeResearchStation() { researchStation = false; };
	std::string toString();

private:
	City city;
	int diseaseCubes;
	bool researchStation;
};