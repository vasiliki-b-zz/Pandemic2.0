#include <iostream>
#include "DirectFlight.h"
#include "Game.h"

DirectFlight::~DirectFlight()
{
}

void DirectFlight::execute()
{
    if(p2 != NULL) {
        executeDispatcher();
    } else {
        std::vector<Card> destinations;
        int count = 0;

        std::cout << "\n~ Where would you like to fly?" << std::endl;

        for (int i = 0; i < player->getHand().size(); i++) {
            if (player->getHand().at(i).getType() == CardType::CITY) {
                destinations.push_back(player->getHand().at(i));
                count++;
                std::cout << "\t" << count << " - " << map->getVertex(player->getHand().at(i).getName())->toString()
                          << std::endl;
            }
        }

        int choice = Game::getUserIntput(1, destinations.size() + 1);

        int index = player->findIndexOfCard(destinations.at(choice - 1).getName(),
                                            CardType::CITY); //Find index of the destination card in player's hand

        if (player->getLocation()->getName() == player->getHand().at(index).getName()) {
            std::cout << "\n(!) You are already at that location!" << std::endl;
            player->incrementActions();
            return;
        }

        player->discardFromHand(index); //Discard that card

        CityVertex *destination = (CityVertex *) map->getVertex(destinations.at(choice - 1).getName());

        player->setLocation(destination);
    }
}

void DirectFlight::executeDispatcher() {
    std::vector<Card> destinations;
    int count = 0;

    std::cout << "\n~ Where would you like to fly?" << std::endl;

    for (int i = 0; i < p2->getHand().size(); i++) {
        if (p2->getHand().at(i).getType() == CardType::CITY) {
            destinations.push_back(p2->getHand().at(i));
            count++;
            std::cout << "\t" << count << " - " << map->getVertex(p2->getHand().at(i).getName())->toString()
                      << std::endl;
        }
    }

    int choice = Game::getUserIntput(1, destinations.size() + 1);

    int index = p2->findIndexOfCard(destinations.at(choice - 1).getName(),
                                        CardType::CITY); //Find index of the destination card in player's hand

    if (player->getLocation()->getName() == p2->getHand().at(index).getName()) {
        std::cout << "\n(!) You are already at that location!" << std::endl;
        p2->incrementActions();
        return;
    }

    player->discardFromHand(index); //Discard that card

    CityVertex *destination = (CityVertex *) map->getVertex(destinations.at(choice - 1).getName());

    player->setLocation(destination);
}
