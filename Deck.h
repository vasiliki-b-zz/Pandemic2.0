#pragma once

#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "Card.h"

template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

class Deck
{
public:
	Deck();
	~Deck();
	bool isEmpty();
	Card* drawBack();
	Card* drawFront();
	void add(Card* c) { cards.push_back(c); };
    void addToFront(Card* c) {cards.insert(cards.begin(),c);};
    void merge(Deck d);
	void discard(Card* c);
	Card* getCardAtIndex(int n);
	std::vector<Card*> getCardsInDeck() { return this->cards;};
	void shuffle();
	int saveInfectionDeck(std::ofstream &file);
    int saveInfectionDiscard(std::ofstream &file);
    int savePlayerDeck(std::ofstream &file);
    int savePlayerDiscard(std::ofstream &file);
    std::string toString();
private:
	std::vector<Card*> cards;
};

