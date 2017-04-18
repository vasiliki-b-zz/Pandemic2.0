#pragma once
#include "Strategy.h"
#include "Board.h"

class DiscoverCure : public Strategy
{
public:
	DiscoverCure(Player* p, Board& board, Deck& deck) { this->player = p; this->board = &board; this->deck = &deck;}
	~DiscoverCure();
	void execute();
private:
	Player* player;
	Board* board;
	Deck* deck;
};

