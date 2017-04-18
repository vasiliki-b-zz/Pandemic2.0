#include <iostream>
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

bool Board::canReduceDiseaseCubes(std::string color, int n) {
	if (color == "RED") {
		if (redDiseaseCubes - n <= 0)
			return false;
		else {
			redDiseaseCubes -= n;
			return true;
		}
	} else if (color == "BLACK") {
		if (blackDiseaseCubes - n <= 0)
			return false;
		else {
			blackDiseaseCubes -= n;
			return true;
		}
	} else if (color == "YELLOW") {
		if (yellowDiseaseCubes - n <= 0)
			return false;
		else {
			yellowDiseaseCubes -= n;
			return true;
		}

	} else if (color == "BLUE") {
		if (blueDiseaseCubes - n <= 0)
			return false;
		else {
			blueDiseaseCubes -= n;
			return true;
		}
	}
}

void Board::setDiseaseCubes(std::string color, int n) {
    if(color == "RED") {
        redDiseaseCubes = n;
    } else if(color == "YELLOW") {
        yellowDiseaseCubes = n;
    } else if(color == "BLACK") {
        blackDiseaseCubes = n;
    } else if(color == "BLUE") {
        blueDiseaseCubes = n;
    }
}

std::string Board::diseaseCubesToSave() {
    std::string ds = "";
    ds+= std::to_string(redDiseaseCubes)    + ",";
    ds+= std::to_string(yellowDiseaseCubes) + ",";
    ds+= std::to_string(blackDiseaseCubes)  + ",";
    ds+= std::to_string(blueDiseaseCubes);
    return ds;
}

int Board::save(std::ofstream &file) {
	if (file.is_open())
	{
		file << this->toStringSave(); //Output board to file
		file.close();
		std::cout << "(OK) File saved successfully!" << std::endl;
	}
	else {
		std::cout << "(!) Error: IO exception..." << std::endl;
	}

	return 0;
}

std::string Board::toStringSave() {
	std::string s = "";
	s+= this->diseaseCubesToSave() + ":";
	s+= std::to_string(getOutbreakMarker()) + ":";
	s+= std::to_string(getInfectionRateIndex()) + ":";
    for(int i = 0; i < 4; i++) {
        s+= std::to_string(cureMarkers[i]);
        if(i < 3) {
            s+= ",";
        }
    }
	s+= ":"; // separator
    for(int i = 0; i < 4; i++) {
        s+= std::to_string(eradicatedMarkers[i]);
        if(i < 3) {
            s+= ",";
        }
    }
	s+= ":" + std::to_string(getResearchStationsLeft());
    return s;

}
