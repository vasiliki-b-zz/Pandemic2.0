#pragma once
#include "Strategy.h"
#include "Board.h"

class DiscoverCure : public Strategy
{
public:
	DiscoverCure(Player* p, Board& board) { this->player = p; this->board = &board; }
	~DiscoverCure();
	void execute();
private:
	Player* player;
	Board* board;
};

