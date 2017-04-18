#pragma once

#include <list>
#include "Graph.h"
#include "Deck.h"
#include "DiseaseColour.h"

class Board
{
public:
	Board() { this->outbreakMarker = 0; this->infectionRateIndex = 0; this->researchStations = 6;};
	~Board();
	void increaseOutbreakMarker() { this->outbreakMarker++; };
	int getOutbreakMarker() { return outbreakMarker; };
	void increaseInfectionRate();
	int getInfectionRate() { return infectionRate[infectionRateIndex]; };
	void addCureMarker(Disease::Colour colour);
	void flipCureMarker(Disease::Colour colour);
	bool hasCure(Disease::Colour colour);
	void decreaseResearchStations() {this->researchStations--;};
	int getResearchStationsLeft() { return this->researchStations;};
	bool canReduceDiseaseCubes(std::string color,int n);
	std::string toString();

private:
	int outbreakMarker;
	int infectionRate[7] = { 2, 2, 2, 3, 3, 4 };
	int infectionRateIndex;
	bool cureMarkers[4] = { false, false, false, false };
	bool eradicatedMarkers[4] = { false, false, false, false };
	int researchStations;
	int redDiseaseCubes = 24;
	int blueDiseaseCubes = 24;
	int blackDiseaseCubes = 24;
	int yellowDiseaseCubes = 24;
};

