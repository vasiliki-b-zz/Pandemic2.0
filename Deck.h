#pragma once

#include <vector>
#include <algorithm>
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
	Card& drawBack();
	Card& drawFront();
	void add(Card* c) { cards.push_back(c); };
	void merge(Deck d);
	void discard(Card* c);
	void shuffle();
private:
	std::vector<Card*> cards;
};

