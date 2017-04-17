//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "OperationStrategy.h"

void OperationStrategy::execute() {
    if(board->getResearchStationsLeft() > 0) {
        player->getLocation()->addResearchStation();
        board->decreaseResearchStations();
    } else {
        std::cout << "Sorry there are no more research stations" << std::endl;
    }
}