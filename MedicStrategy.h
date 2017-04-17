//
// Created by Quentin on 4/16/17.
//

#ifndef PANDEMIC_MEDICSTRATEGY_H
#define PANDEMIC_MEDICSTRATEGY_H


#include "Strategy.h"
#include "Board.h"

class MedicStrategy : public Strategy{
public:
    MedicStrategy(Player* p, Graph& graph, Board& board) { this->player = p;this->map = &graph; this->board = &board; }
    ~MedicStrategy() {};
    void execute();
private:
    Player* player;
    Board* board;
    Graph* map;
};


#endif //PANDEMIC_MEDICSTRATEGY_H
