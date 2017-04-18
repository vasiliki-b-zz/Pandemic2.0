//
// Created by Andrés Kebe on 2017-04-16.
//
// TODO IMPLEMENT OBSERVER!!!!!

#include <iostream>
#include "Infection.h"

using namespace std;



Infection::Infection() {}

Infection::~Infection() {}


void Infection::infectCity(Board &board, CityVertex *city, int n,vector<Player*> players, Graph &graph, CityVertex* cityThatJustOutbreaked) {
    string color = DiseaseColourEnumToString(city->getColour());
    if (board.canReduceDiseaseCubes(color,n))
        if (city->getDiseaseCubes() == 3){
            cout<<"There are 3 disease cubes! Outbreak will take place\n";
            outbreak(board,city,players,graph);
        }
        else {
            city->addDiseaseCubes(n);
        }

    else
        cout << "Game over!";
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

void Infection::infectEpidemic(Board &board, CityVertex *city,vector<Player*> players, Graph &graph,CityVertex* cityThatJustOutbreaked) {
    cout << "Begin infection\n";
    board.increaseInfectionRate();
    int numbersToAdd = 3 - city->getDiseaseCubes();
    if (numbersToAdd != 3)
        outbreak(board,city,players,graph);
    infectCity(board,city,numbersToAdd,players,graph);
}

void Infection::outbreak (Board &board, CityVertex *city,vector<Player*> players, Graph &graph){

}