#pragma once

#include <string>
#include "Card.h"
#include "PawnColour.h"

class RoleCard : public Card
{
public:
	RoleCard() : Card() { this->colour = PawnColour::NONE; };
	RoleCard(std::string name, PawnColour::PawnColour colour, std::string description) : Card(name, description, CardType::ROLE) { this->colour = colour; };
	~RoleCard();
	PawnColour::PawnColour getColour() { return colour; };
	std::string print();
	std::string toString();
	std::string toStringSave();

private:
	PawnColour::PawnColour colour;
};

