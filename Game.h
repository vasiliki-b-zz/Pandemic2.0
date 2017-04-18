#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "Board.h"
#include "Graph.h"
#include "Player.h"
#include "TurnTaker.h"
#include "Infection.h"


class Game
{
public:
	Game() : board(board), map(map), referenceCard(referenceCard), roleDeck(roleDeck), infectionDeck(infectionDeck), playerDeck(playerDeck), infectionDiscard(infectionDiscard), playerDiscard(playerDiscard) { numOfPlayers = 0; gameOver = false; };
	~Game();

    Graph getMap() {return map;};
    Board getBoard() {return board;};
	Deck getInfectionDeck() { return infectionDeck;};
	Deck getInfectionDiscard() { return infectionDiscard;};
	Deck getPlayerDeck() { return playerDeck;};
	Deck getPlayerDiscard() { return playerDiscard;};
    std::vector<Player*> getPlayers() { return players;}
	std::string getCurrentPlayerName() { return currentPlayer; };

    void setMap(Graph g) { this->map = g; };
    void setBoard(Board b) { this->board = b;};
    void setPlayers(std::vector<Player*> p) {this->players = p;};

	void discardCard (Player* player);

	static int getUserIntput(int min, int max);
	bool hasResearcher = false;

private:
	const int MIN_PLAYERS = 2;
	const int MAX_PLAYERS = 4;
	const int MAX_CARDS = 7;
	const int INIT_CITIES_INFECTED = 9;
	const int TWO_PLAYER_HAND = 4;
	const int THREE_PLAYER_HAND = 3;
	const int FOUR_PLAYER_HAND = 2;

	int numOfPlayers;
	bool gameOver;
	std::vector<Player*> players;
	Graph map;
	Board board;
	Card referenceCard;
	Deck roleDeck, infectionDeck, playerDeck, infectionDiscard, playerDiscard;
	std::string currentPlayer;
    Infection infection;

	void configureBoard(); //Infection cards are configured in here
	void configureRoleCards();
	void configureReferenceCards();
	void configureEventCards();
	void configureEpidemicCards();

	bool setNumOfPlayers(int n);
	void addPlayer(Player* player);
	void remmovePlayer(int playerNumber);
	void initializePlayers();
	void initializeInfectedCities();

	void start();
	void save();
	void load();
	void quit();
	void configure();
	void helpMenu(std::string input);
	void chooseBasicAction(Player* p, int i, TurnTaker* turnTaker);
	void chooseSpecialAction(Player* p, int i, TurnTaker* turnTaker);
	void roleActions(Player* p, int i, TurnTaker* turnTaker, bool);
	void play();


public:
	void run();
};
