#include "BuildResearchStation.h"
#include "Game.h"


BuildResearchStation::~BuildResearchStation()
{
}

void BuildResearchStation::execute()
{
    if (!player->getLocation()->hasResearchStation())
    {
        int index = player->findIndexOfCard(player->getLocation()->getCity().getName(), CardType::CITY);
        if (index > 0) {
            player->discardFromHand(index);
            player->getLocation()->addResearchStation();
        }
        else {
            std::cout << "\n(!) You need the City Card for " << player->getLocation()->getCity().toString()
                      << " to complete this action!" << std::endl;
            player->incrementActions();
        }
    }
    else {
        std::cout << "\n(!) Your current city already has a Reasearch Station! " << std::endl;
        player->incrementActions();
    }

}
