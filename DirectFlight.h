#pragma once
#include "Strategy.h"
#include "Graph.h"

class DirectFlight : public Strategy
{
public:
	DirectFlight(Player* p, Player* p2, Graph& map) { this->player = p; this->p2 = p2; this->map = &map; }
	~DirectFlight();
	void execute();
	void executeDispatcher();
private:
	Player* player;
	Graph* map;
	Player* p2;
};

