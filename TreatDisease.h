#pragma once
#include "Strategy.h"
#include "Board.h"

class TreatDisease : public Strategy
{
public:
	TreatDisease(Player* p, Board& board) { this->player = p; this->board = &board; }
	void execute();
private:
	Player* player;
	Board* board;
};

