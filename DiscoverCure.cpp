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

	std::vector<int> blueCards, yellowCards, blackCards, redCards;

	for (int i = 0; i < player->getHand().size(); i++)
	{
		if (player->getHand().at(i).getType() == CardType::CITY) //Get city cards only
		{
			if (player->getHand().at(i).getDescription() == DiseaseColourEnumToString(Disease::BLUE))
				blueCards.push_back(i);
			else if (player->getHand().at(i).getDescription() == DiseaseColourEnumToString(Disease::YELLOW))
				yellowCards.push_back(i);
			else if (player->getHand().at(i).getDescription() == DiseaseColourEnumToString(Disease::BLACK))
				blackCards.push_back(i);
			else if (player->getHand().at(i).getDescription() == DiseaseColourEnumToString(Disease::RED))
				redCards.push_back(i);
		}
	}

	std::vector<std::string> options;

	if (blueCards.size() >= 5)
	{
		options.push_back("BLUE");
		std::cout << "\n~ You can cure the BLUE disease by discarding the following cards: " << std::endl;
		for (int i = 0; i < blueCards.size(); i++)
			std::cout << "\n\t o " << player->getHand().at(i).getName() << std::endl;
	}
	else if (yellowCards.size() >= 5)
	{
		options.push_back("YELLOW");
		std::cout << "\n~ You can cure the YELLOW disease by discarding the following cards: " << std::endl;
		for (int i = 0; i < yellowCards.size(); i++)
			std::cout << "\n\t o " << player->getHand().at(i).getName() << std::endl;
	}
	else if (blackCards.size() >= 5)
	{
		options.push_back("BLACK");
		std::cout << "\n~ You can cure the BLACK disease by discarding the following cards: " << std::endl;
		for (int i = 0; i < blackCards.size(); i++)
			std::cout << "\n\t o " << player->getHand().at(i).getName() << std::endl;
	}
	else if (redCards.size() >= 5)
	{
		options.push_back("RED");
		std::cout << "\n~ You can cure the RED disease by discarding the following cards: " << std::endl;
		for (int i = 0; i < redCards.size(); i++)
			std::cout << "\n\t o " << player->getHand().at(i).getName() << std::endl;
	}
	else
	{
		std::cout << "\n(!) You do not have enough city cards of the same colour to complete this action!" << std::endl;
		player->incrementActions();player->incrementActions();
		return;
	}

	std::cout << "\n~ What disease would you like to cure?" << std::endl;

	for (int i = 0; i < options.size(); i++)
		std::cout << "\t" << i + 1 << " - " << options.at(i) << std::endl;

	int choice = Game::getUserIntput(1, options.size());
	board->flipCureMarker(DiseaseColourStringToEnum(options.at(choice)));

}
