//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "ResearcherStrategy.h"

void ResearcherStrategy::execute() {
    std::string input = "";
    CityVertex* cv;
    int researchIndex;
    if(canGetResearcherCard) {
        for(int i = 0; i < players.size(); i++) {
            if (players.at(i)->getRoleSave().getName() == "Researcher") {
                researchIndex = i;
                cv = players.at(i)->getLocation();
            }
        }
        for(int i = 0; i < players.size(); i++) {
            if(cv!= NULL && i !=researchIndex && players.at(i)->getLocation()->getName() == cv->getName()) {
                std::cout << "Which card would you like to get?" << std::endl;
                for(int j = 0; j < players.at(i)->getHand().size(); j++) {
                    if(players.at(i)->getHand().at(j).getType() == CardType::CITY) {
                        std::cout << j << "- " << players.at(i)->findCardAtIndex(j).getName() << std::endl;
                    }
                }
                std::cin >> input;
                //swapping the cards
                player->addToHand(players.at(researchIndex)->findCardAtIndex(std::stoi(input)));
                players.at(researchIndex)->discardFromHand(std::stoi(input));
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
        player->discardFromHand(cardToGive);

    }
}
