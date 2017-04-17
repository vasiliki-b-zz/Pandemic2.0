#include <iostream>
#include <random>
#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
}

bool Deck::isEmpty()
{
	if (cards.size() == 0)
		return true;
	return false;
}

Card& Deck::drawBack()
{
	try
	{
		Card* temp = cards.back();
		cards.pop_back();
		return *temp;
	}
	catch (int e)
	{
		std::cout << "No cards in the deck!" << std::endl;
	}
}

Card& Deck::drawFront()
{
	try
	{
		Card* temp = cards.front();
		pop_front(cards);
		return *temp;
	}
	catch (int e)
	{
		std::cout << "No cards in the deck!" << std::endl;
	}
}

void Deck::merge(Deck d)
{
	for (int i = d.cards.size() - 1; i >= 0; i--)
	{
		cards.push_back(d.cards.at(i));
		d.cards.pop_back();
	}
}

void Deck::discard(Card* c)
{
	//TODO
}

void Deck::shuffle()
{
	std::cout << "Shuffling cards" << std::endl;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(this->cards.begin(), this->cards.end(), g);
	std::cout << "Cards have been shuffled" << std::endl;

//	std::srand(std::time(0));
//	std::random_shuffle(cards.begin(), cards.end());
}

Card* Deck::getCardAtIndex(int n) {
	Card* card = cards.at(n);
	cards.erase(cards.begin() + n);
	return cards.at(n);
}
