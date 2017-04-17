#pragma once
#include "Strategy.h"
#include "Graph.h"
#include "CityVertex.h"

class ShuttleFlight : public Strategy
{
public:
	ShuttleFlight(Player* p, Graph& map) { this->player = p; this->map = &map;}
	~ShuttleFlight();
	void execute();
private:
	Player* player;
	Graph* map;
};

