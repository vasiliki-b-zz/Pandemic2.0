#include "TreatDisease.h"
#include "Game.h"

void TreatDisease::execute()
{
    if (player->getLocation()->getDiseaseCubes() <= 0)
    {
        std::cout << "\n(!) There are no Disease Cubes in the city you are in!" << std::endl;
        player->incrementActions();
        return;
    }

    if (board->hasCure(player->getLocation()->getCity().getColour()))
    {
        player->getLocation()->removeAllDiseaseCubes();
        std::cout << "\n~ You have cured the " << player->getLocation()->getCity().getColour() << " disease at your current location!" << std::endl;
        std::cout << "\n~ Disease Cubes at " << player->getLocation()->getCity().getName() << ": " << player->getLocation()->getDiseaseCubes() << std::endl;
    }
    else
    {
        if(player->getRoleSave().getName() == "Medic") {
            player->getLocation()->removeAllDiseaseCubes();
        } else {
            player->getLocation()->removeDiseaseCubes(1);
        }
        std::cout << "\n~ You have treated the " << player->getLocation()->getCity().getColour() << " disease at your current location!" << std::endl;
        std::cout << "\n~ Disease Cubes at " << player->getLocation()->getCity().getName() << ": " << player->getLocation()->getDiseaseCubes() << std::endl;
    }
}


