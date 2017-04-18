//
// Created by Quentin on 4/8/17.
//

#include"Game.h"

#ifndef PANDEMIC_GAMEBUILDER_H
#define PANDEMIC_GAMEBUILDER_H


class GameBuilder {
public:
    GameBuilder(Game* g) { this->m_game = g; }
    //Get the build Game from the Builder
    Game* getGame() { return m_game; }
    //build a generic empty Game
    virtual void map() = 0;
    virtual void players() = 0;
    virtual void gameEngine() = 0;
    virtual void board() = 0;
    virtual void infectionDeck() = 0;
    virtual void infectionDiscard() = 0;
    virtual void playerDeck() = 0;
    virtual void playerDiscard() = 0;
protected:
    Game* m_game;
    Graph graph;
    std::vector<Player*> currentPlayers;
    Board theBoard;
    Deck theInfectionDeck;
    Deck theInfectionDiscard;
    Deck thePlayerDeck;
    Deck thePlayerDiscard;

};

class SaveGameBuilder : public GameBuilder {
public:
    SaveGameBuilder(Game *g): GameBuilder(g) {};
    virtual void map();
    virtual void players();
    virtual void gameEngine();
    virtual void board();
    virtual void infectionDeck();
    virtual void infectionDiscard();
    virtual void playerDeck();
    virtual void playerDiscard();
};

class LoadGameBuilder : public GameBuilder {
public:
    LoadGameBuilder(Game *g): GameBuilder(g) {};
    virtual void map();
    virtual void players();
    virtual void gameEngine();
    virtual void board();
    virtual void infectionDeck();
    virtual void infectionDiscard();
    virtual void playerDeck();
    virtual void playerDiscard();
};


#endif //PANDEMIC_GAMEBUILDER_H
