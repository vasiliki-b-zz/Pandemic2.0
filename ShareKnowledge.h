#pragma once
#include "Strategy.h"

class ShareKnowledge : public Strategy
{
public:
	void execute(Player* p, CityVertex* c);
};

