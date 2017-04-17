//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "ResearcherStrategy.h"

void ResearcherStrategy::execute() {
    std::string input = "";
    if(canGetResearcherCard) {
        for(Player* p : players) {
            if(p->getRoleSave().getName() == "Researcher") {
                for(int i = 0; p->getHand().size(); i++) {
                    if(p->getHand().at(i).getType() == CardType::CITY) {
                        std::cout << "Which card would you like to get?" << std::endl;
                        std::cout << i << "- " << p->getHand().at(i).getName() << std::endl;
                        std::cin >> input;

                    }
                }
                //swapping the cards
                player->addToHand(player->findCardAtIndex(std::stoi(input)));
                p->discardFromHand(std::stoi(input));
            }
        }
    } else {
        int cardToGive;
        int playerNumberInVector;
        for(int i = 0; player->getHand().size(); i++) {
            if(player->getHand().at(i).getType() == CardType::CITY) {
                std::cout << "Which card would you like to give?" << std::endl;
                std::cout << i << "- " << player->getHand().at(i).getName() << std::endl;

                input.clear();
                std::cin >> input;
                cardToGive = std::stoi(input);
            }
        }
        for(int i = 0; i < players.size(); i++) {
            if(players.at(i)->getName() != player->getName()) {
                std::cout << "Who would you like to give this card to?" << std::endl;
                std::cout << i << " - " << players.at(i)->getName() << std::endl;

                input.clear();
                std::cin >> input;
                playerNumberInVector = std::stoi(input);
            }
        }

        players.at(playerNumberInVector)->addToHand(players.at(playerNumberInVector)->findCardAtIndex(cardToGive));
        p->discardFromHand(cardToGive);

    }
}
