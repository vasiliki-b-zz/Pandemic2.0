//
// Created by Quentin on 4/17/17.
//

#ifndef PANDEMIC_OPERATIONSTRATEGY_H
#define PANDEMIC_OPERATIONSTRATEGY_H


#include "Strategy.h"
#include "Board.h"

class OperationStrategy : public Strategy {
public:
    OperationStrategy(Player* p, Graph& graph, Board& board) { this->player = p; this->map = &graph;this->board = &board;}
    ~OperationStrategy() {};
    void execute();
private:
    Player* player;
    Graph* map;
    Board* board;
};


#endif //PANDEMIC_OPERATIONSTRATEGY_H
