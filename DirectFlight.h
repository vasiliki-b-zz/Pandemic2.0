#pragma once
#include "Strategy.h"
#include "Graph.h"

class DirectFlight : public Strategy
{
public:
	DirectFlight(Player* p, Graph& map) { this->player = p; this->map = &map; }
	~DirectFlight();
	void execute();
private:
	Player* player;
	Graph* map;
};

