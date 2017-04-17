#pragma once
#include "Strategy.h"

class TurnTaker
{
private:
	Strategy *strategy;
public:
	TurnTaker() {};
	TurnTaker(Strategy *initStrategy) { this->strategy = initStrategy; }
	void setStrategy(Strategy *newStrategy) { this->strategy = newStrategy; }
	void executeStrategy() { this->strategy->execute(); }
};
