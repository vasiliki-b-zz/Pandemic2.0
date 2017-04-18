//
// Created by Quentin on 4/17/17.
//

#ifndef PANDEMIC_RESEARCHERSTRATEGY_H
#define PANDEMIC_RESEARCHERSTRATEGY_H


#include "Strategy.h"

class ResearcherStrategy : public Strategy {
public:
    ResearcherStrategy(Player* p, std::vector<Player*> players, bool canGetResearcherCard, Deck &deck) { this->player = p;this->players = players; this->canGetResearcherCard = canGetResearcherCard; this->deck = &deck;};
    ~ResearcherStrategy() {};
    void execute();
private:
    Player* player;
    std::vector<Player*> players;
    bool canGetResearcherCard;
    Deck* deck;
};


#endif //PANDEMIC_RESEARCHERSTRATEGY_H
