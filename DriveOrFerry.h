#pragma once
#include "Strategy.h"
#include "Graph.h"

class DriveOrFerry : public Strategy
{
public:
	DriveOrFerry(Player* p, Graph& map) { this->player = p; this->map = &map;}
	void execute();
private:
	Player* player;
	Graph* map;
};

