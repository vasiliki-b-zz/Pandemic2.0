#pragma once
#pragma once

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "Util.h"
#include "RoleCard.h"
#include "CityVertex.h"
#include "CardType.h"
#include "Graph.h"

class Player
{
public:
	Player(std::string name) { this->name = name; };
	~Player();
	bool operator==(Player v) const;
	std::string getName() const { return name; };
	void setName(std::string name) { this->name = name; };
	CityVertex* getLocation() const { return currentLocation; };
	void setLocation(CityVertex* city) { this->currentLocation = city; };
	std::string getRole() { return roleCard.print(); };
	RoleCard getRoleSave() { return roleCard; };
	void setRole(RoleCard roleCard) { this->roleCard = roleCard; this->pawnColour = roleCard.getColour(); };
	PawnColour::PawnColour getPawnColour() { return pawnColour; };
	void addToHand(Card playerCard) { playerHand.push_back(playerCard); };
	void discardFromHand(int index);
	void discardFromHand(Card playerCard);
	int findIndexOfCard(std::string name, CardType::CardType type);
	std::vector<Card> getHand() const { return playerHand; };
	int save(std::ofstream &file, std::vector<Player*> players);
	std::vector<Player*> static loadPlayers(std::ifstream &file, Graph &graph);
	std::string toString(std::vector<Player*> players);
	int getActions(){return actions;}
	void setActions(int a){actions = a;}
	int decrementActions(){return actions--;}
	int incrementActions(){return actions++;}
	CityVertex* researcherCity(std::vector<Player*> players);
	Card findCardAtIndex(int);

private:
	std::string name;
	CityVertex* currentLocation;
	RoleCard roleCard;
	PawnColour::PawnColour pawnColour;
	std::vector<Card> playerHand;
	int actions = 4;
};

