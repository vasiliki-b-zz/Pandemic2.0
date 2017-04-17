#pragma once
#include "Strategy.h"
#include "Graph.h"

class CharterFlight : public Strategy
{
public:
	CharterFlight(Player* p, Graph& map) { this->player = p; this->map = &map;}
	~CharterFlight();
	void execute();
private:
	Player* player;
	Graph* map;
};

