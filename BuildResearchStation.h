#pragma once
#include "Strategy.h"

class BuildResearchStation : public Strategy
{
public:
	BuildResearchStation(Player* p) { this->player = p; }
	~BuildResearchStation();
	void execute();
private:
	Player* player;
};