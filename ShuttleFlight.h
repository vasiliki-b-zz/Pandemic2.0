#pragma once
#include "Strategy.h"
#include "Graph.h"
#include "CityVertex.h"
#include "Board.h"

class ShuttleFlight : public Strategy
{
public:
	ShuttleFlight(Player* p, Graph& map, Board& board) { this->player = p; this->map = &map; this->board = &board;}
	~ShuttleFlight();
	void execute();
private:
	Player* player;
	Graph* map;
	Board* board;
};

