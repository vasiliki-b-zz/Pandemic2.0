//
// Created by Quentin on 4/8/17.
//

#include "GameBuilder.h"
void SaveGameBuilder::map() {
    std::string filePath("../IO_Files/currentMap.txt");
    std::ofstream inFile(filePath.c_str());

    graph = m_game->getMap();
    graph.save(inFile);
}

void SaveGameBuilder::players() {
    std::string filePath("../IO_Files/currentPlayers.txt");
    std::ofstream inFile(filePath.c_str());

    currentPlayers = m_game->getPlayers();
    currentPlayers.at(0)->save(inFile,currentPlayers);
}

void SaveGameBuilder::gameEngine() {
    std::string filePath("../IO_Files/currentEngine.txt");
    std::ofstream inFile(filePath.c_str());

    std::string s = "";
    s+= m_game->getCurrentPlayerName() + " ";
    for(Player* p: currentPlayers) {
        if(p->getName() == m_game->getCurrentPlayerName()) {
            s+= std::to_string(p->getActions());
        }
    }
    if (inFile.is_open())
    {
        inFile << s; //Output turn and number of action to file
        inFile.close();
        std::cout << "(OK) File saved successfully!" << std::endl;
    }
    else
        std::cout << "(!) Error: IO exception..." << std::endl;
}

void SaveGameBuilder::board() {
    std::string filePath("../IO_Files/currentBoard.txt");
    std::ofstream inFile(filePath.c_str());

    theBoard = m_game->getBoard();
    theBoard.save(inFile);
}

void SaveGameBuilder::infectionDeck() {
    std::string filePath("../IO_Files/currentInfectionDeck.txt");
    std::ofstream inFile(filePath.c_str());

    theInfectionDeck = m_game->getInfectionDeck();
    theInfectionDeck.saveInfectionDeck(inFile);
}

void SaveGameBuilder::infectionDiscard() {
    std::string filePath("../IO_Files/currentInfectionDiscard.txt");
    std::ofstream inFile(filePath.c_str());

    theInfectionDiscard = m_game->getInfectionDiscard();
    theInfectionDiscard.saveInfectionDiscard(inFile);
}

void SaveGameBuilder::playerDeck() {
    std::string filePath("../IO_Files/currentPlayerDeck.txt");
    std::ofstream inFile(filePath.c_str());

    thePlayerDeck = m_game->getPlayerDeck();
    thePlayerDeck.savePlayerDeck(inFile);
}

void SaveGameBuilder::playerDiscard() {
    std::string filePath("../IO_Files/currentPlayerDiscard.txt");
    std::ofstream inFile(filePath.c_str());

    thePlayerDiscard = m_game->getPlayerDiscard();
    thePlayerDiscard.savePlayerDiscard(inFile);
}

void LoadGameBuilder::map() {
    std::string filePath("../IO_Files/currentMap.txt");
    std::ifstream inFile(filePath.c_str());

    graph.loadMap(inFile);
    m_game->setMap(graph);
}

void LoadGameBuilder::players() {
    std::string filePath("../IO_Files/currentPlayers.txt");
    std::ifstream inFile(filePath.c_str());

    currentPlayers = Player::loadPlayers(inFile, graph);
    m_game->setPlayers(currentPlayers);
}

void LoadGameBuilder::gameEngine() {}

void LoadGameBuilder::board() {}

void LoadGameBuilder::infectionDeck() {}

void LoadGameBuilder::infectionDiscard() {}

void LoadGameBuilder::playerDeck() {}

void LoadGameBuilder::playerDiscard() {}