//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "ContigencyStrategy.h"

void ContigencyStrategy::execute() {
    std::string input = "";
    for(int i = 0; i < deck->getCardsInDeck().size(); i++) {
        if(deck->getCardsInDeck().at(i)->getType()== CardType::EVENT) {
            std::cout << "Would you like this event card?\n" << i << " - " << deck->getCardAtIndex(i)->getName() << std::endl;
        }
    }
    std::cin >> input;
    p->addToHand(*deck->getCardAtIndex(std::stoi(input)));
}