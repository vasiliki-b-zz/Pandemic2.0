#pragma once
#include "Strategy.h"
#include "Board.h"

class BuildResearchStation : public Strategy
{
public:
	BuildResearchStation(Player* p, Board& board, Deck& deck) { this->player = p; this->board = &board;this->deck = &deck;};
	~BuildResearchStation();
	void execute();
private:
	Player* player;
	Board* board;
	Deck* deck;
};