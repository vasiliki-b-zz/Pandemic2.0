//
// Created by Quentin on 4/17/17.
//

#pragma once

#include "Strategy.h"
#include "Deck.h"

class ContigencyStrategy : public Strategy{
public:
    ContigencyStrategy(Player* p, Deck &deck) { this->p = p; this->deck = &deck;};
    ~ContigencyStrategy();
    void execute();
private:
    Player* p;
    Deck* deck;
};
