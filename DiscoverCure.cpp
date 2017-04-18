#include "DiscoverCure.h"
#include "Game.h"

DiscoverCure::~DiscoverCure()
{
}

void DiscoverCure::execute()
{
	if (!player->getLocation()->hasResearchStation())
	{
		std::cout << "\n(!) You must be in a city with a Reasearch Station to complete this action!" << std::endl;
		player->incrementActions();
		return;
	}

	std::vector<Card*> blueCards, yellowCards, blackCards, redCards;

	for (int i = 0; i < player->getHand().size(); i++)
	{
		if (player->getHand().at(i)->getType() == CardType::CITY) //Get city cards only
		{
			if (player->getHand().at(i)->getDescription() == DiseaseColourEnumToString(Disease::BLUE))
				blueCards.push_back(player->getHand().at(i));
			else if (player->getHand().at(i)->getDescription() == DiseaseColourEnumToString(Disease::YELLOW))
				yellowCards.push_back(player->getHand().at(i));
			else if (player->getHand().at(i)->getDescription() == DiseaseColourEnumToString(Disease::BLACK))
				blackCards.push_back(player->getHand().at(i));
			else if (player->getHand().at(i)->getDescription() == DiseaseColourEnumToString(Disease::RED))
				redCards.push_back(player->getHand().at(i));
		}
	}

	if(player->getRoleSave()->getName() == "Scientist") {
		if (blueCards.size() >= 4) {
			std::cout << "\n~ You are curing the BLUE disease!" << std::endl;
			for (int i = 0; i < blueCards.size(); i++)
				player->discardFromHand(blueCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("BLUE"));
		} else if (yellowCards.size() >= 4) {
			std::cout << "\n~ You are curing the YELLOW disease!" << std::endl;
			for (int i = 0; i < yellowCards.size(); i++)
				player->discardFromHand(yellowCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("YELLOW"));
		} else if (blackCards.size() >= 4) {
			std::cout << "\n~ You are curing the BLACK disease!" << std::endl;
			for (int i = 0; i < blackCards.size(); i++)
				player->discardFromHand(blackCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("BLACK"));
		} else if (redCards.size() >= 4) {
			std::cout << "\n~ You are curing the RED disease!" << std::endl;
			for (int i = 0; i < redCards.size(); i++)
				player->discardFromHand(redCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("RED"));
		} else {
			std::cout << "\n(!) You do not have enough city cards of the same colour to complete this action!"
					  << std::endl;
			player->incrementActions();
			return;
		}
	} else {
		if (blueCards.size() >= 5) {
			std::cout << "\n~ You are curing the BLUE disease!" << std::endl;
			for (int i = 0; i < blueCards.size(); i++)
				player->discardFromHand(blueCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("BLUE"));
		} else if (yellowCards.size() >= 5) {
			std::cout << "\n~ You are curing the YELLOW disease!" << std::endl;
			for (int i = 0; i < yellowCards.size(); i++)
				player->discardFromHand(yellowCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("YELLOW"));
		} else if (blackCards.size() >= 5) {
			std::cout << "\n~ You are curing the BLACK disease!" << std::endl;
			for (int i = 0; i < blackCards.size(); i++)
				player->discardFromHand(blackCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("BLACK"));
		} else if (redCards.size() >= 5) {
			std::cout << "\n~ You are curing the RED disease!" << std::endl;
			for (int i = 0; i < redCards.size(); i++)
				player->discardFromHand(redCards.at(i));
			board->flipCureMarker(DiseaseColourStringToEnum("RED"));
		} else {
			std::cout << "\n(!) You do not have enough city cards of the same colour to complete this action!"
					  << std::endl;
			player->incrementActions();
			return;
		}
	}
}
