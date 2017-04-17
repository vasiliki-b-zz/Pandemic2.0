#include <iostream>
#include "CharterFlight.h"
#include "Game.h"

CharterFlight::~CharterFlight()
{
}

void CharterFlight::execute()
{
    int index = player->findIndexOfCard(player->getLocation()->getCity().getName(), CardType::CITY); //Find current city card in player's hand
    if (index > 0)
    {
        std::cout << "\n~ Where would you like to fly?" << std::endl;
        int count = 0;

        for (int i = 0; i < map->getVertexList().size(); i++)
            if (map->getVertexList().at(i)->getName() != player->getLocation()->getName())
            {
                count++;
                std::cout << "\t" << count << " - " << map->getVertexList().at(i)->toString() << std::endl;
            }

        int choice = Game::getUserIntput(1, map->getVertexList().size());

        player->discardFromHand(index); //Discard current city card

        CityVertex* destination = (CityVertex*)map->getVertexList().at(choice);
        player->setLocation(destination);
    }
    else
        std::cout << "\n(!) You need the City Card for " << player->getLocation()->getCity().toString() << " to complete this action!" << std::endl;
        player->incrementActions();
}
