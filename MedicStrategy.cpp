//
// Created by Quentin on 4/16/17.
//

#include "MedicStrategy.h"
#include "Game.h"

void MedicStrategy::execute() {
    if(board->hasCure(player->getLocation()->getColour())) {
        player->getLocation()->removeAllDiseaseCubes();
    }
}

