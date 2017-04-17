//
// Created by Quentin on 4/8/17.
//

#include "GameBuilder.h"
void SaveGameBuilder::map() {
    std::string filePath("../IO_Files/currentMap.txt");
    std::ofstream inFile(filePath.c_str());

    graph = m_game->getMap();
    std::cout << graph.toString() << std::endl;
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

    std::string s = m_game->getCurrentPlayerName() + " " + std::to_string(m_game->getCurrentTurn());
    if (inFile.is_open())
    {
        inFile << s; //Output turn and number of action to file
        inFile.close();
        std::cout << "(OK) File saved successfully!" << std::endl;
    }
    else
        std::cout << "(!) Error: IO exception..." << std::endl;
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