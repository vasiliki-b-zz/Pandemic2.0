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
//    void createNewGameProduct() { m_game = new Game;}
    virtual void map() = 0;
    virtual void players() = 0;
    virtual void gameEngine() = 0;
protected:
    Game* m_game;
    Graph graph;
    std::vector<Player*> currentPlayers;

};

class SaveGameBuilder : public GameBuilder {
public:
    SaveGameBuilder(Game *g): GameBuilder(g) {};
    virtual void map();
    virtual void players();
    virtual void gameEngine();
};

class LoadGameBuilder : public GameBuilder {
public:
    LoadGameBuilder(Game *g): GameBuilder(g) {};
    virtual void map();
    virtual void players();
    virtual void gameEngine();
};


#endif //PANDEMIC_GAMEBUILDER_H
