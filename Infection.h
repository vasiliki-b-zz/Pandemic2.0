//
// Created by Andrés Kebe on 2017-04-16.
//

#include "Board.h"
#include "Player.h"
#include "Deck.h"
#include <iostream>

#ifndef PANDEMIC_INFECTION_H
#define PANDEMIC_INFECTION_H


class Infection {
public:
    Infection();

    virtual ~Infection();

    void infectCity(Board &board, CityVertex *city, int n,std::vector<Player*> players, Graph &graph);
    void infectEpidemic(Board &board, CityVertex *city,std::vector<Player*> players, Graph &graph);
    void outbreak(Board &board, CityVertex *city,std::vector<Player*> players, Graph &graph);
private:
    Deck deck;

};


#endif //PANDEMIC_INFECTION_H
