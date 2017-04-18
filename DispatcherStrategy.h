//
// Created by Quentin on 4/17/17.
//

#pragma once


#include "Strategy.h"
#include "TurnTaker.h"
#include "Board.h"

class DispatcherStrategy : public Strategy {
public:
    DispatcherStrategy(Player* p, std::vector<Player* > players, Graph &map, Board &board) {this->p = p; this->players = players; this->map = &map; this->board = &board; };
    ~DispatcherStrategy() {};
    void execute();
    void moveToACityWithAnotherPawn(Player* p);
    void moveAPawnAsIfOwn(Player* p);
private:
    Player* p;
    std::vector<Player* > players;
    Graph* map;
    TurnTaker* turnTaker = new TurnTaker();
    Board* board;
};

