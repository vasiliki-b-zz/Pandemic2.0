#pragma once

#include <list>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "Deck.h"
#include "DiseaseColour.h"

class Board
{
public:
	Board() { this->outbreakMarker = 0; this->infectionRateIndex = 0; this->researchStations = 6; this->redDiseaseCubes = 24; this->yellowDiseaseCubes = 24; this->blueDiseaseCubes = 24; this->blackDiseaseCubes = 24;};
	~Board();
	void increaseOutbreakMarker() { this->outbreakMarker++; };
	int getOutbreakMarker() { return outbreakMarker; };
	void increaseInfectionRate();
	int getInfectionRate() { return infectionRate[infectionRateIndex]; };
	int getInfectionRateIndex() {return this->infectionRateIndex;};
	void setInfectionRate(int n) { this->infectionRateIndex = n;};
	void addCureMarker(Disease::Colour colour);
	void flipCureMarker(Disease::Colour colour);
	bool hasCure(Disease::Colour colour);
	void decreaseResearchStations() {this->researchStations--;};
	int getResearchStationsLeft() { return this->researchStations;};
	void setCureMarkers(bool[4]);
	void setEradicatedMarkers(bool[4]);
	bool canReduceDiseaseCubes(std::string color,int n);
	void setDiseaseCubes(std::string, int);
	std::string diseaseCubesToSave();
	int save(std::ofstream &file);
	std::string toString();
	std::string toStringSave();

private:
	int outbreakMarker;
	int infectionRate[7] = { 2, 2, 2, 3, 3, 4 };
	int infectionRateIndex;
	bool cureMarkers[4] = { false, false, false, false };
	bool eradicatedMarkers[4] = { false, false, false, false };
	int researchStations,redDiseaseCubes,blueDiseaseCubes,blackDiseaseCubes,yellowDiseaseCubes;
};

