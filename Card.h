#pragma once

#include <string>
#include "CardType.h"

class Card
{
public:
	Card() { this->name = ""; this->description = ""; this->type = CardType::NONE; };
	Card(std::string name, std::string description, CardType::CardType type) { this->name = name; this->description = description; this->type = type; };
	~Card();
	std::string getName() const { return name; };
	std::string getDescription() const { return description; };
	CardType::CardType getType() const { return type; };
	virtual std::string print();
	virtual std::string toString();
	std::string getCard();

private:
	std::string name;
	std::string description;
	CardType::CardType type;
};



