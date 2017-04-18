//
// Created by Quentin on 4/17/17.
//

#include <iostream>
#include "DispatcherStrategy.h"
#include "DriveOrFerry.h"
#include "DirectFlight.h"
#include "CharterFlight.h"
#include "ShuttleFlight.h"

void DispatcherStrategy::execute() {
    std::string input = "";
    std::string pawn = "";
    std::cout << "What method would you like to do?\n 1 - Move any pawn to any city containing another pawn\n 2 - Move a pawn as his own" << std::endl;

    std::cin >> input;

    std::cout << "Which pawn would you like to move?" << std::endl;

    for(int i = 0; i < players.size(); i++) {
        if(players.at(i)->getName() != p->getName()) {
            std::cout << i << " - " << players.at(i)->getName() << " at location " << players.at(i)->getLocation()->getName() << std::endl;
        }
    }
    std::cin >> pawn;

    if(std::stoi(input) == 1) {
        moveToACityWithAnotherPawn(players.at(std::stoi(pawn)));
    } else if(std::stoi(input) == 2) {
        moveAPawnAsIfOwn(players.at(std::stoi(pawn)));
    }
}

void DispatcherStrategy::moveAPawnAsIfOwn(Player *p1) {
    std::string input = "";
    int action;
    do {
        input.clear();
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "\t1 - Drive or Ferry: Move your pawn to an adjacent city." << std::endl;
        std::cout << "\t2 - Direct Flight: Discard a card to move your pawn to the city pictured on it." << std::endl;
        std::cout
                << "\t3 - Charter Flight: Discard the card showing your current city and move to any city on the board."
                << std::endl;
        std::cout
                << "\t4 - Shuttle Flight: Move to a city containing a reasearch station if your pawn is in a city containing a station."
                << std::endl;

        std::cin >> input;
        action = std::stoi(input);
    } while(action != 1 && action != 2 && action != 3 && action != 4);

    switch (action) {
        case 1: //DRIVE OR FERRY
        {
            turnTaker->setStrategy(new DriveOrFerry(p1, *map));
            turnTaker->executeStrategy();
            break;
        }
        case 2: //DIRECT FLIGHT
        {
            turnTaker->setStrategy(new DirectFlight(p1, p, *map));
            turnTaker->executeStrategy();

            break;
        }
        case 3: //CHARTER FLIGHT
        {
            turnTaker->setStrategy(new CharterFlight(p1, p, *map));
            turnTaker->executeStrategy();
            //============================================================================================TODO don't decrement action if player doesnt have card
            break;
        }
        case 4: //SHUTTLE FLIGHT
        {
            turnTaker->setStrategy(new ShuttleFlight(p1, *map, *board));
            turnTaker->executeStrategy();
            //============================================================================================TODO don't decrement action if no research station on current location
            break;
        }
    }
};

void DispatcherStrategy::moveToACityWithAnotherPawn(Player *p) {
    std::cout << "Which city would you like to move to?" << std::endl;
    std::string input = "";
    for(int i = 0; i < players.size(); i++) {
        if(players.at(i)->getLocation()->getName() != p->getLocation()->getName()) {
            std::cout << i << " - " << players.at(i)->getLocation()->getName() << std::endl;
        }
    }
    std::cin >> input;
    p->setLocation(players.at(std::stoi(input))->getLocation());
};
