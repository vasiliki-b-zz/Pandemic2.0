#include <iostream>
#include <fstream>
#include <sstream>
#include "Player.h"

//Player::Player()
//{
//}

Player::~Player()
{
}

bool Player::operator==(Player v) const
{
	if (this->name.compare(v.name) == 0) //Players must have unique names
		return true;
	return false;
}

void Player::discardFromHand(int index)
{
	playerHand.erase(playerHand.begin() + index);
}

void Player::discardFromHand(Card* playerCard)
{
	for (int i = 0; i < playerHand.size(); i++)
		if (playerCard->getType() == playerHand.at(i)->getType() && playerCard->getName() == playerHand.at(i)->getName())
			playerHand.erase(playerHand.begin() + i);
}

int Player::findIndexOfCard(std::string name, CardType::CardType type)
{
	for (int i = 0; i < playerHand.size(); i++)
		if (playerHand.at(i)->getName() == name && playerHand.at(i)->getType() == type)
			return i;
	return -1;
}

Card* Player::findCardAtIndex(int n) {
    return this->playerHand.at(n);
}

int Player::save(std::ofstream &file, std::vector<Player*> players) {
	if (file.is_open())
	{
		file << toString(players); //Output players to file
		file.close();
		std::cout << "(OK) File saved successfully!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;

	return 0;
}

std::vector<Player*> Player::loadPlayers(std::ifstream &file, Graph &graph) {
	std::vector<Player*> players;

	if (file.is_open())
	{
		std::string line;
		while(std::getline(file, line)) {
			std::vector<std::string> playerAndHand;
			boost::split(playerAndHand,line, boost::is_any_of(":"));
			assert(playerAndHand.size() == 2);

			auto parseNameAndProps = [](std::string input) {
				std::vector<std::string> nameAndProps;
				boost::split(nameAndProps, input, boost::is_any_of("("));
				assert(nameAndProps.size() == 2);

				return nameAndProps;
			};

			auto cleanRole = [](std::string input) {
				return input.replace(input.find(")"),1,"");
			};

			auto parseProps = [] (std::string input) {
				std::vector<std::string> roleParams;
				boost::split(roleParams, input, boost::is_any_of(";"));
				assert(roleParams.size() == 4);
				return roleParams;
			};

            auto parseCardsProps = [] (std::string input) {
                std::vector<std::string> cardParams;
                boost::split(cardParams, input, boost::is_any_of(","));
                assert(cardParams.size() == 3);
                return cardParams;
            };

			auto nameAndProps = parseNameAndProps(playerAndHand[0]);
			auto playerName = nameAndProps[0];
			auto params = parseProps(cleanRole(nameAndProps[1]));
			auto roleName = params[0];
			auto roleColor = params[1];
			auto roleDescription = params[2];
			auto location = params[3];

			RoleCard* card = new RoleCard(roleName,PawnColourStringToEnum(roleColor), roleDescription);
			Player* p = new Player(playerName);
			p->setRole(card);
			p->setLocation(dynamic_cast<CityVertex*>(graph.getVertex(location)));

            std::vector<std::string> cards;
            auto cardString = playerAndHand[1];
            cardString = cardString.erase(cardString.find("{"), 1);
            cardString = cardString.erase(cardString.find("}"), 1);

            boost::split(cards, cardString, boost::is_any_of(";"));
            assert(cards.size() > 0);
            for(auto &card : cards) {
                trim(card);
                auto cardParams = parseCardsProps(card);
                auto cardName = cardParams[0];
                auto cardColour = cardParams[1];
                auto cardType = cardParams[2];

                Card* cardToAdd = new Card(cardName, cardColour, CardTypeStringToEnum(cardType));
				p->addToHand(cardToAdd);
            }
			players.push_back(p);
		}

		file.close();
	}
	else {
        std::cout << "(!) Error: IO exception..." << std::endl;
    }
}

CityVertex* Player::researcherCity(std::vector<Player*> players) {
	for(Player* p : players) {
        if(p->getRoleSave()->getName() == "Researcher") {
            return p->getLocation();
        }
	}
}

void Player::addContingencyPlannerCard(Card* card) {
	if(this->getRoleSave()->getName() == "Contigency Planner") {
		this->extraCardContingencyPlanner = card;
	}
}

std::string Player::toString(std::vector<Player*> players) {
	std::string s = "";
	for(int i = 0; i < players.size(); i++) {
		s += players.at(i)->getName() + "(" + players.at(i)->getRoleSave()->toStringSave() + ";" + players.at(i)->getLocation()->getName() + ")" + ":{";
		for(int j = 0; j < players.at(i)->getHand().size(); j++) {
			s+= players.at(i)->getHand().at(j)->getCard() + ";";
		}
		s+= "}\n";
	}
	return s;
}