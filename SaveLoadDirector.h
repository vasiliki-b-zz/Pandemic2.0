//
// Created by Quentin on 4/8/17.
//

#ifndef PANDEMIC_SAVELOADDIRECTOR_H
#define PANDEMIC_SAVELOADDIRECTOR_H


#include "GameBuilder.h"

class SaveLoadDirector {
public:
    void setGameBuilder(GameBuilder* gameBuilder) {
        m_gameBuilder = gameBuilder;
    }

    Game* getGame() {
        return m_gameBuilder->getGame();
    }

    void constructGame() {
        m_gameBuilder->map();
        m_gameBuilder->players();
//        m_gameBuilder->gameEngine();
//        m_gameBuilder->board();
//        m_gameBuilder->infectionDeck();
//        m_gameBuilder->infectionDiscard();
//        m_gameBuilder->playerDeck();
//        m_gameBuilder->playerDiscard();
    }
    void saveGame() {
        m_gameBuilder->map();
        m_gameBuilder->players();
        m_gameBuilder->gameEngine();
        m_gameBuilder->board();
        m_gameBuilder->infectionDeck();
        m_gameBuilder->infectionDiscard();
        m_gameBuilder->playerDeck();
        m_gameBuilder->playerDiscard();
    };
private:
    GameBuilder* m_gameBuilder;
};


#endif //PANDEMIC_SAVELOADDIRECTOR_H
