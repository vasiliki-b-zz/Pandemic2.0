#pragma once
#include "Strategy.h"
#include "Graph.h"

class CharterFlight : public Strategy
{
public:
	CharterFlight(Player* p, Player* p2, Graph& map) { this->player = p; this->p2 = p2; this->map = &map;}
	~CharterFlight();
	void execute();
	void executeDispatcher();
private:
	Player* player;
	Player* p2;
	Graph* map;
};

