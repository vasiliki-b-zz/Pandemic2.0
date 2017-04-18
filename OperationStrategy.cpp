//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "OperationStrategy.h"

void OperationStrategy::execute() {
    std::string input = "";
    std::cout << "Which action would you like to do?\n 1 - Build a research station in current city without discarding a city card\n 2 - Once per turn, move from a research staton to any city by discard any city card" << std::endl;
    std::cin >> input;

    if(std::stoi(input) == 1 && board->getResearchStationsLeft() > 0) {
        player->getLocation()->addResearchStation();
        board->decreaseResearchStations();
    } else if(std::stoi(input) == 1 && board->getResearchStationsLeft() == 0){
        std::cout << "Sorry there are no more research stations" << std::endl;
        player->incrementActions();
    } else if(std::stoi(input) == 2) {
        if(player->getLocation()->hasResearchStation()) {
            std::string city = "";
            std::string cityMove = "";
            std::cout << "Which card would you like to discard?" << std::endl;
            for(int i = 0; i < player->getHand().size(); i++) {
                if(player->getHand().at(i)->getType() == CardType::CITY) {
                    std::cout << i << " - " << player->getHand().at(i)->getName() << std::endl;
                }
            }
            std::cin >> city;

            player->discardFromHand(std::stoi(city), deck);

            std::cout << "Where would you like to go?" << std::endl;
            for(int i = 0; i < map->getVertexList().size(); i++) {
                if(player->getLocation()->getName() != map->getVertexList().at(i)->getName()) {
                    std::cout << i << " - " << map->getVertexList().at(i)->getName() << std::endl;
                }
            }
            std::cin >> cityMove;

            player->setLocation(dynamic_cast<CityVertex*>(map->getVertexList().at(std::stoi(cityMove))));
        } else {
            std::cout << " Your location doesn't have a research station" << std::endl;
            player->incrementActions();
        }
    }
}