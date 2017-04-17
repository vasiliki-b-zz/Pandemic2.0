#include "Board.h"

Board::~Board()
{
}

void Board::increaseInfectionRate()
{
	if (infectionRateIndex < (sizeof(infectionRate) / sizeof(*infectionRate)))
		infectionRateIndex++;
	else
		return;
}

void Board::addCureMarker(Disease::Colour colour)
{
	if (colour == Disease::YELLOW)
		cureMarkers[0] = !cureMarkers[0];
	else if (colour == Disease::RED)
		cureMarkers[1] = !cureMarkers[1];
	else if (colour == Disease::BLUE)
		cureMarkers[2] = !cureMarkers[2];
	else if (colour == Disease::BLACK)
		cureMarkers[3] = !cureMarkers[3];
}

void Board::flipCureMarker(Disease::Colour colour)
{
	if (colour == Disease::YELLOW)
		eradicatedMarkers[0] = !eradicatedMarkers[0];
	else if (colour == Disease::RED)
		eradicatedMarkers[1] = !eradicatedMarkers[1];
	else if (colour == Disease::BLUE)
		eradicatedMarkers[2] = !eradicatedMarkers[2];
	else if (colour == Disease::BLACK)
		eradicatedMarkers[3] = !eradicatedMarkers[3];
}

bool Board::hasCure(Disease::Colour colour)
{
	return cureMarkers[colour];
}

std::string Board::toString()
{
	std::string s = "";
	s += "\n========================================\n";
	s += "\n============ PANDEMIC BOARD ============\n";
	s += "\n========================================\n";
	s += "Outbreak Marker:\t" + std::to_string(outbreakMarker);
	s += "\nInfection Rate:\t\t" + std::to_string(infectionRate[infectionRateIndex]);
	s += "\nCure Markers:\t\t";
	for (int i = 0; i < sizeof(cureMarkers); i++)
		if (cureMarkers[i] == true)
		{
			if (eradicatedMarkers[i] == true)
				s += "[0] "; //Eradicated
			else
				s += "[X] "; //Cured
		}
		else
			s += "[ ] "; //TODO add colours
	s += "\n========================================\n";
	return s;
}
