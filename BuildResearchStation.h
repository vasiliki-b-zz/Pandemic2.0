#pragma once
#include "Strategy.h"
#include "Board.h"

class BuildResearchStation : public Strategy
{
public:
	BuildResearchStation(Player* p, Board& board) { this->player = p; this->board = &board;}
	~BuildResearchStation();
	void execute();
private:
	Player* player;
	Board* board;
};