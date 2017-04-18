//
// Created by Andrés Kebe on 2017-04-16.
//
// TODO IMPLEMENT OBSERVER!!!!!

#include <iostream>
#include "Infection.h"

using namespace std;



Infection::Infection() {}

Infection::~Infection() {}

// todo add the methods that are commented out.
// todo if more than 3 diseases cubes -> outbreak.

void Infection::infectCity(Board &board, CityVertex *city, int n,vector<Player*> players, Graph &graph) {
//    string color = DiseaseColourEnumToString(city->getColour());
//    if (canReduceDiseaseCubes(color,n))
//        city->addDiseaseCubes(n);
//    else
//        cout << "Game over!";
//        observer pattern
    for(Player* p : players) {
        if(p->getRoleSave()->getName() == "Quarantine Specialist") {
            if(p->getLocation()->getName() == city->getName()) {
                cout << "Can't infect this city, as the quarantine specialist is in it. Thank you QS for saving us.\n";
                return;
            } else {
                for(Vertex* v : graph.getNeighbours(p->getLocation())) {
                    if(v->getName() == city->getName()) {
                        cout << "Can't infect this city, as the quarantine specialist is in a neighbouring city. Thank you QS for saving us.\n";
                        return;
                    }
                }
            }
        }
    }
}

void Infection::infectEpidemic(Board &board, CityVertex *city,vector<Player*> players, Graph &graph) {
    cout << "Begin infection\n";
    board.increaseInfectionRate();
    int numbersToAdd = 3 - city->getDiseaseCubes();
    infectCity(board,city,numbersToAdd,players,graph);
    if (numbersToAdd != 3)
        outbreak(board,city,players,graph);
}

// todo
void Infection::outbreak (Board &board, CityVertex *city,vector<Player*> players, Graph &graph){
    cout << "OUTBREAK MOTHERFUCKER";
}