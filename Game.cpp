#include <algorithm>
#include "Game.h"
#include "Util.h"
#include "TurnTaker.h"
#include "DriveOrFerry.h"
#include "DirectFlight.h"
#include "CharterFlight.h"
#include "ShuttleFlight.h"
#include "BuildResearchStation.h"
#include "DiscoverCure.h"
#include "TreatDisease.h"
#include "ShareKnowledge.h"
#include "SaveLoadDirector.h"
#include "MedicStrategy.h"
#include "ResearcherStrategy.h"
#include "OperationStrategy.h"
#include "ContigencyStrategy.h"
#include "DispatcherStrategy.h"

Game::~Game()
{
}

bool Game::setNumOfPlayers(int n)
{
	if (n > MAX_PLAYERS || n < MIN_PLAYERS)
		return false;
	else
		numOfPlayers = n;
	return true;	
}

void Game::addPlayer(Player* player)
{
	players.push_back(player);
}

void Game::remmovePlayer(int playerNumber)
{
	int numOfPlayers = players.size(); //To ommit signed/unsigned mismatch warning...

	if (playerNumber < 0 || playerNumber >= numOfPlayers)
		return;

	for (int i = 0; i < numOfPlayers; i++)
	{
		if (i == playerNumber)
		{
			players.erase(players.begin() + i);
			break;
		}
	}
}

void Game::configureBoard()
{
	std::cout << "\n~ Configuring game board...";

	board = Board();

	std::string filePath("../IO_Files/map_input.txt");
	std::ifstream inFile(filePath.c_str());

    if (inFile.is_open())
    {
        //try
        std::string line;
        while (std::getline(inFile, line)) //Read file line by line
        {
            std::vector<std::string> cityAndNeighbours;
            boost::split(cityAndNeighbours, line, boost::is_any_of(":"));
            assert(cityAndNeighbours.size() == 2);

            trim(cityAndNeighbours[0]);
            trim(cityAndNeighbours[1]);

            auto parseCityAndProps = [](std::string input) {
                std::vector<std::string> nameAndProps;
                boost::split(nameAndProps, input, boost::is_any_of("("));
                assert(nameAndProps.size() == 2);

                return nameAndProps;
            };

            auto parseParams = [](std::string input) {
                std::vector<std::string> params;
                boost::split(params, input, boost::is_any_of(")"));
                assert(params.size() == 2);
                return params;
            };

            auto nameAndProps = parseCityAndProps(cityAndNeighbours[0]);
            auto cityName = nameAndProps[0];
            auto params = parseParams(nameAndProps[1]);
            auto color = params[0];
            CityVertex* cv;

            Card* infectionCard = new Card(cityName, color, CardType::INFECTION); //Create infection cards as well
            Card* cityCard = new Card(cityName, color, CardType::CITY);
            infectionDeck.add(infectionCard);
            playerDeck.add(cityCard);
            City city = City(cityName, DiseaseColourStringToEnum(color));

            for(Vertex* v : map.getVertexList()) {
                if(v->getName() == cityName) {
                    cv = dynamic_cast<CityVertex* >(v);
                    goto addNeighbours;
                }
            }

            for(Edge edge : map.getEdgeList()) {
                if(edge.getStart()->getName() == cityName) {
                    map.add(edge.getStart());
                    cv = dynamic_cast<CityVertex*>(edge.getStart());
                    goto addNeighbours;
                } else if (edge.getEnd()->getName() == cityName) {
                    map.add(edge.getEnd());
                    cv = dynamic_cast<CityVertex*>(edge.getEnd());
                    goto addNeighbours;
                }
            }


            cv = new CityVertex(city); //Create vertex with vName and vColour
            map.add(dynamic_cast<Vertex*>(cv));

            addNeighbours:
                std::vector<std::string> neighbours;
                auto neighboursString = cityAndNeighbours[1];
                neighboursString = neighboursString.erase(neighboursString.find("{"), 1);
                neighboursString = neighboursString.erase(neighboursString.find("}"), 1);

                boost::split(neighbours, neighboursString, boost::is_any_of(")"));
                assert(neighbours.size() > 0); // will fail if map is not connected!!
                neighbours.pop_back();


                for (auto &neighbour : neighbours) {
                    trim(neighbour);
                    bool go = false;
                    auto neighborNameAndProps = parseCityAndProps(neighbour);
                    auto neighborCityName = neighborNameAndProps[0];

                    for(Vertex* isInList: map.getVertexList()) {
                        if (isInList->getName() == neighborCityName) {
                            map.addEdge(dynamic_cast<Vertex *>(cv), isInList);
                            go = true;
                            break;
                        }
                    }

                    if(!go) {
                        auto neighborColor = neighborNameAndProps[1];

                        City neighborCity = City(neighborCityName, DiseaseColourStringToEnum(neighborColor));
                        CityVertex *edge = new CityVertex(neighborCity); //Create vertex with vName and vColour
                        map.addEdge(dynamic_cast<Vertex *>(cv), dynamic_cast<Vertex *>(edge));
                    }
                }
        }

        inFile.close();
        std::cout << board.toString() << std::endl << map.toString() << std::endl;
        std::cout << "~ The board is all set!" << std::endl;
    }
    else
        std::cout << "(!) Error: IO exception..." << std::endl;
	CityVertex* start = dynamic_cast<CityVertex*>(map.getVertex("Atlanta"));
	start->addResearchStation();
	board.decreaseResearchStations();
}

void Game::configureRoleCards()
{
	std::cout << "\n~ Configuring role cards...";

	std::string filePath("../IO_Files/role_input.txt");
	std::ifstream inFile(filePath.c_str());

	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line)) //Read file line by line
		{
			std::istringstream in_stream(line);
			std::string key, value;

			if (std::getline(in_stream, key, ':'))
			{
				std::string name, colour, description;
				name = key.substr(0, key.find("(")); //Extract card name from key

				int start = key.find("(") + 1;
				int end = key.find(")") - start;

				colour = key.substr(start, end); //Extract pawn colour from key

				if (std::getline(in_stream, value))
				{
					trim(value);
					description = value;

					Card* roleCard = new RoleCard(name, PawnColourStringToEnum(colour), description);
					roleDeck.add(roleCard);
				}
			}
		}
		inFile.close();

		std::cout << "\n~ Role cards created!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;
}

void Game::configureReferenceCards()
{
	std::cout << "\n~ Configuring reference cards...";

	std::string filePath("../IO_Files/reference_input.txt");
	std::ifstream inFile(filePath.c_str());

	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line)) //Read file line by line
		{
			std::istringstream in_stream(line);
			std::string key, value;

			if (std::getline(in_stream, key, ':'))
			{
				std::string name, description;

				name = key;
				trim(name);

				if (std::getline(in_stream, value))
				{
					trim(value);
					description = value;

					referenceCard = Card(name, description, CardType::REFERENCE);
				}
			}
		}
		inFile.close();

		std::cout << "\n~ Reference cards created!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;

}

void Game::configureEventCards() //=====================================================================TODO Fix this
{
	std::cout << "\n~ Configuring event cards...";

	std::string filePath("../IO_Files/event_input.txt");
	std::ifstream inFile(filePath.c_str());

	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line)) //Read file line by line
		{
			std::istringstream in_stream(line);
			std::string key, value;

			if (std::getline(in_stream, key, ':'))
			{
				std::string name, description;

				name = key;
				trim(name);

				if (std::getline(in_stream, value))
				{
					trim(value);
					description = value;

					Card* eventCard = new Card(name, description, CardType::EVENT);
					playerDeck.add(eventCard);
				}
			}
		}
		inFile.close();

		std::cout << "\n~ Event cards created!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;
}

void Game::configureEpidemicCards()//=====================================================================TODO Fix this
{
	std::cout << "\n~ Configuring Epidemic cards...";

	std::string filePath("../IO_Files/epidemic_input.txt");
	std::ifstream inFile(filePath.c_str());

	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line)) //Read file line by line
		{
			std::istringstream in_stream(line);
			std::string key, value;

			if (std::getline(in_stream, key, ':'))
			{
				std::string name, description;

				name = key;
				trim(name);

				if (std::getline(in_stream, value))
				{
					trim(value);
					description = value;

					Card* epidemicCard = new Card(name, description, CardType::EPIDEMIC);
					playerDeck.add(epidemicCard);

				}
			}
		}
        playerDeck.shuffle();
		inFile.close();

		std::cout << "\n~ Epidemic cards created!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;
}

void Game::initializePlayers()
{
	std::string input = "";

	std::cout << "\nHow many players are there? (2-4)" << std::endl;

	while (input != "2" && input != "3" && input != "4")
	{
		std::cout << "> ";
		std::cin >> input;
	}

	numOfPlayers = std::stoi(input.c_str());

	CityVertex* start = dynamic_cast<CityVertex*>(map.getVertex("Atlanta"));

	for (int i = 0; i < numOfPlayers; i++)
	{
		std::cout << ".....................................";
		std::cout << "\nPLAYER " << i + 1 << ", please enter your name: ";
		std::cin >> input;

		Player* player = new Player(input);

		std::cout << "\nHello [" << player->getName() << "]! :)\n" << std::endl;

		std::cout << "~ Drawing a role card for [PLAYER " << i + 1 << "] " << player->getName() << "...\n" << std::endl;
		roleDeck.shuffle();

		RoleCard* playerRoleCard = dynamic_cast<RoleCard*>(roleDeck.drawBack());
		player->setRole(playerRoleCard);
        if(playerRoleCard->getName() == "Researcher") {
            hasResearcher = true;
        }

		std::cout << playerRoleCard->print() << std::endl;

		std::cout << "~ Drawing player cards for PLAYER " << i + 1 << " [" << player->getName() << "]...\n" << std::endl;
		playerDeck.shuffle();

		switch (numOfPlayers)
		{
			case 2:
				for (int i = 0; i < TWO_PLAYER_HAND; i++)
				{
					Card* playerCard = playerDeck.drawBack();
					player->addToHand(playerCard);
				}
				std::cout << "~ PLAYER " << i + 1 << " [" << player->getName() << "] has " << TWO_PLAYER_HAND << " player cards.\n" << std::endl;
				break;
			case 3:
				for (int i = 0; i < THREE_PLAYER_HAND; i++)
				{
					Card* playerCard = playerDeck.drawBack();
					player->addToHand(playerCard);
				}
				std::cout << "~ PLAYER " << i + 1 << " [" << player->getName() << "] has " << THREE_PLAYER_HAND << " player cards.\n" << std::endl;
				break;
			case 4:
				for (int i = 0; i < FOUR_PLAYER_HAND; i++)
				{
					Card* playerCard = playerDeck.drawBack();
					player->addToHand(playerCard);
				}
				std::cout << "~ PLAYER " << i + 1 << " [" << player->getName() << "] has " << FOUR_PLAYER_HAND << " player cards.\n" << std::endl;
				break;
		}

		std::cout << "~ Setting pawn on start location - " << start->toString() << std::endl;
		player->setLocation(start);

		addPlayer(player);
	}
}

void Game::initializeInfectedCities()
{
	std::cout << "\n~ Infecting " << INIT_CITIES_INFECTED << " cities..." << std::endl;
	std::cout << "~ Shuffling infection cards..." << std::endl;
	infectionDeck.shuffle();

	std::cout << "~ Drawing infection cards...\n" << std::endl;

	CityVertex* infectedCity;
	Card* infectionCard;
	std::string s = "";

	for (int i = 0; i < INIT_CITIES_INFECTED; i++)
	{
		infectionCard = infectionDeck.drawBack();

		if (i < 3)
		{
			infectedCity = dynamic_cast<CityVertex*>(map.getVertex(infectionCard->getName()));
			infection.infectCity(board,infectedCity,3,players,map,NULL);
			s += "\to   " + infectedCity->getCity().toString() + "\n";
//			if (i == 2)
//			{
//				std::cout << "These cities have been infected with 3 disease cubes!\n" << s << std::endl;
//				s = "";
//			}

		}

		if (i >= 3 && i < 6)
		{
			infectedCity = dynamic_cast<CityVertex*>(map.getVertex(infectionCard->getName()));
			infection.infectCity(board,infectedCity,2,players,map,NULL);
			s += "\to   " + infectedCity->getCity().toString() + "\n";
//			if (i == 5)
//			{
//				std::cout << "These cities have been infected with 2 disease cubes!\n" << s << std::endl;
//				s = "";
//			}
		}
		if (i >= 6)
		{
			infectedCity = dynamic_cast<CityVertex*>(map.getVertex(infectionCard->getName()));
			infection.infectCity(board,infectedCity,1,players,map,NULL);
			s += "\to   " + infectedCity->getCity().toString() + "\n";
//			if (i == 8)
//			{
//				std::cout << "These cities have been infected with 1 disease cube!\n" << s;
//				s = "";
//			}
		}
		infectionDiscard.add(infectionCard); //===================================TODO: Might have to change from deck to list?
	}
}

int Game::getUserIntput(int min, int max)
{
	int input = 0;

	std::cout << "> ";
	std::cin >> input;

	//if (command == "menu" || command == "details" || command == "map" || command == "board" || command == "help")
	//{
	//	helpMenu(command);
	//	//system("PAUSE");
	//}

	while (std::cin.fail() || input < min || input > max) // If choice is a string or out of range
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "> ";
		std::cin >> input;
	}

	return input;
}

void Game::start()
{
	std::ifstream inFile("../IO_Files/welcome.txt");
	std::string line;

	if (inFile.is_open())
	{
		while (std::getline(inFile, line))
		{
			std::cout << line << std::endl;
		}
		inFile.close();
	}
	else
	{
		std::cout << "(!) Error: Could not open file ..\\IO_Files\\welcome.txt" << std::endl;
		return;
	}

	std::string input = "";
	std::cout << "\nEnter a command from the list below:" << std::endl;
	std::cout << "\t1 - Play!\n\t2 - Help\n\t3 - Quit" << std::endl;

	while (input != "1" && input != "2" && input != "3")
	{
		std::cout << "> ";
		std::cin >> input;
	}

	if (input == "2")
	{
		//======================================================================TODO ?
	}
	else if (input == "3")
	{
		quit();
	}
}

void Game::quit()
{
	std::cout << "\n~ Thank you for playing Pandemic! See you next time :)" << std::endl;
	system("PAUSE");
	exit(0);
}

void Game::configure()
{
	configureBoard();
	std::cout << ".................................................." << std::endl;
	configureRoleCards();
	std::cout << ".................................................." << std::endl;
	configureReferenceCards();
	std::cout << ".................................................." << std::endl;
	configureEventCards();
	std::cout << ".................................................." << std::endl;
	initializeInfectedCities();
	//std::cout << ".................................................." << std::endl;
	//setDifficulty();
	std::cout << ".................................................." << std::endl;
	initializePlayers();
    std::cout << ".................................................." << std::endl;
    configureEpidemicCards();
    std::cout << ".................................................." << std::endl;
	std::cout << "~ Everything is set!" << std::endl;
}

void Game::helpMenu(std::string input)
{
	if (input == "menu")
	{
		std::cout << "main menu" << std::endl;
	}
	else if (input == "details")
	{
		std::cout << "player details" << std::endl;
	}
	else if (input == "map")
	{
		std::cout << "current map" << std::endl;
	}
	else if (input == "board")
	{
		std::cout << "current board" << std::endl;
	}
	else if (input == "help")
	{
		std::string help = "\n~ These commands are available at any time during gameplay.\n\n\t\'menu'\t\tView the main menu.\n\t\'details\'\tView your player details.\n\t\'map\'\t\tView the current map.\n\t\'board\'\t\tView the current board.\n\t\'help\'\t\tView this menu.";
		std::cout << help << std::endl;
	}
}

void Game::chooseBasicAction(Player* p, int i, TurnTaker* turnTaker)
{
	if(p->getRoleSave()->getName() == "Medic") {
		turnTaker->setStrategy(new MedicStrategy(p, map, board));
		turnTaker->executeStrategy();
	}
	switch (i) {
		case 1: //DRIVE OR FERRY
		{
			turnTaker->setStrategy(new DriveOrFerry(p, map));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 2: //DIRECT FLIGHT
		{
			turnTaker->setStrategy(new DirectFlight(p,NULL, map));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 3: //CHARTER FLIGHT
		{
			turnTaker->setStrategy(new CharterFlight(p,NULL, map));
			turnTaker->executeStrategy();
			//============================================================================================TODO don't decrement action if player doesnt have card
			p->decrementActions();
			break;
		}
		case 4: //SHUTTLE FLIGHT
		{
			turnTaker->setStrategy(new ShuttleFlight(p, map, board));
			turnTaker->executeStrategy();
			//============================================================================================TODO don't decrement action if no research station on current location
			p->decrementActions();
			break;
		}
	}

}

void Game::chooseSpecialAction(Player* p, int i, TurnTaker* turnTaker)
{
	switch (i) {
		case 1: //BUILD RESEARCH STATION
		{
			turnTaker->setStrategy(new BuildResearchStation(p, board));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 2: //DISCOVER CURE
		{
			turnTaker->setStrategy(new DiscoverCure(p, board));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 3: //TREAT DISEASE
		{
			turnTaker->setStrategy(new TreatDisease(p, board));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 4: //SHARE KNOWLEDGE
		{
			//==============================================================================================TODO
//			turnTaker->setStrategy(new ShareKnowledge());
//			turnTaker->executeStrategy();

//			std::cout << "\Share Knowledge\n";
			p->decrementActions();
			break;
		}
	}
}

void Game::discardCard(Player* player){
	while (player->getHand().size() > MAX_CARDS) {
		std::cout << "\n(!) You must discard " << player->getHand().size() - MAX_CARDS << " cards." << std::endl;
		std::cout << "\n(!) Displaying " << player->getName()<< "'s hand:" << std::endl;
		std::vector<Card*> hand = player->getHand();
		for (int g = 0; g < hand.size(); g++) {
			std::cout << "\t(" << g + 1 << ") : " << hand.at(g)->getName()<<std::endl;

		}
		std::cout
				<< "Which card would you like to discard? (If you choose an event card, it will be played)\n";
		int choice;
		std::cin >> choice;
		choice--;
		Card* chosen = hand.at(choice);
		if (chosen->getType() == CardType::CITY) {
			std::cout << "Discarding " << chosen->getName() << std::endl;
			player->discardFromHand(choice);
		}
		else if (chosen->getType() == CardType::EVENT){
			std::cout << "Playing event card ";
			// do event
		}
		std::cout << player->getName() << " now has " << player->getHand().size() << " cards\n";
	}

}


void Game::roleActions(Player* p, int i, TurnTaker* turnTaker, bool checks) {
	switch(i) {
		case 1: {
			turnTaker->setStrategy(new ResearcherStrategy(p,players, checks));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 2: {
			turnTaker->setStrategy(new DispatcherStrategy(p,players, map, board));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 3: {
			turnTaker->setStrategy(new OperationStrategy(p,map, board));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
		case 4: {
			turnTaker->setStrategy(new ContigencyStrategy(p, playerDiscard));
			turnTaker->executeStrategy();

			p->decrementActions();
			break;
		}
	}
}

void Game::play()
{
	std::string input = "";

	helpMenu("help");
	std::cout << "\n~ Ready to play? (y/n)" << std::endl;

	while (input != "y" && input != "n")
	{
		std::cout << "> ";
		std::cin >> input;

		if (input == "n")
			quit();
	}

	while (!gameOver)
	{
		for (int i = 0; i < players.size(); i++) //For each player
		{
			TurnTaker* turnTaker = new TurnTaker;
			input = "";
			//int actions = 4; //Number of actions a player can make
			players.at(i)->setActions(4);
			std::cout << "==================================================" << std::endl;
			std::cout << "PLAYER " << i + 1 << " [" << players.at(i)->getName() << "]'s Turn" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			//***** TAKE 4 ACTIONS *****
			chooseAction:
			while(players.at(i)->getActions() > 0) // Choose an action 4 times
			{
				std::cout<<"Player " << i+1 << " 's hand is \n";
				int counter = 0;
				std::cout<<"[ ";
				for (auto a: players.at(i)->getHand()){
					std::cout << "(" << counter + 1 <<") " << a->getName()<<" ";
					counter++;
				}
				std::cout<<"]";
                bool canGetResearcherCard = false;
				do
				{
					std::cout << "\n~ Choose an action:" << std::endl;

					std::cout << "\t1 - BASIC ACTION" << std::endl;
					std::cout << "\t2 - SPECIAL ACTION" << std::endl;

                    if(hasResearcher) {
                        CityVertex* cv = players.at(i)->researcherCity(players);
                        if(players.at(i)->getLocation()->getName() == cv->getName()) {
                            std::cout << "\t3 - Role ACTION" << std::endl;
                            canGetResearcherCard = true;
                        }
                    } else {
                        if (players.at(i)->getRoleSave()->getName() == "Researcher" ||
                            players.at(i)->getRoleSave()->getName() == "Dispatcher" ||
                            players.at(i)->getRoleSave()->getName() == "Operations Expert" ||
                            players.at(i)->getRoleSave()->getName() == "Contigency Planner") {
                            std::cout << "\t3 - Role ACTION" << std::endl;
                        }
                    }

					std:: cout << "\n\t0 - END TURN" << std::endl;

					input.clear();

					std::cout << "> ";
					std::cin >> input;

					if (input == "menu" || input == "details" || input == "map" || input == "board" || input == "help")
					{
						helpMenu(input);
						//system("PAUSE");
					}

				} while (input != "0" && input != "1" && input != "2" && input != "3");

				if (input == "0")
					break;

				if (input == "1") // If Basic Action is chosen
				{
					do
					{
						std::cout << "\t~ BASIC ACTIONS ~" << std::endl;

						std::cout << "\t1 - Drive or Ferry: Move your pawn to an adjacent city." << std::endl;
						std::cout << "\t2 - Direct Flight: Discard a card to move your pawn to the city pictured on it." << std::endl;
						std::cout << "\t3 - Charter Flight: Discard the card showing your current city and move to any city on the board." << std::endl;
						std::cout << "\t4 - Shuttle Flight: Move to a city containing a reasearch station if your pawn is in a city containing a station." << std::endl;

						std::cout << "\n\t0 - BACK" << std::endl;

						input.clear();

						std::cout << "> ";
						std::cin >> input;

						if (input == "menu" || input == "details" || input == "map" || input == "board" || input == "help")
						{
							helpMenu(input);
							//system("PAUSE");
						}

						if (input == "0")
							goto chooseAction; //HACKS

					} while (input != "1" && input != "2" && input != "3" && input != "4");

					chooseBasicAction(players.at(i), stoi(input), turnTaker);

					std::cout << "\n~ Your current location is: " << players.at(i)->getLocation()->toString() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
					std::cout << "~ Actions left: " << players.at(i)->getActions() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
				}

				else if (input == "2") // If Special Action is chosen
				{
					do
					{
						std::cout << "\t~ SPECIAL ACTIONS ~" << std::endl;

						std::cout << "\t1 - Build A Research Station: Discard the card showing your current city to build a Research Station there." << std::endl;
						std::cout << "\t2 - Discover A Cure: Discard 5 cards of the same colour to cure the disease of that colour. Your pawn must be in a city containing a research station." << std::endl;
						std::cout << "\t3 - Treat Disease: Remove a disease cube from the city your pawn occupies. If the cure has been found, remove all the cubes of that color from the city" << std::endl;
						std::cout << "\t4 - Share Knowledge: Pass a card from one player to another. Both players' pawns must be in the city pictured on the card that is passed." << std::endl;

						std::cout << "\n\t0 - BACK" << std::endl;

						input.clear();

						std::cout << "> ";
						std::cin >> input;

						if (input == "menu" || input == "details" || input == "map" || input == "board" || input == "help")
						{
							helpMenu(input);
							//system("PAUSE");
						}

						if (input == "0")
							goto chooseAction; //HACKS

					} while (input != "1" && input != "2" && input != "3" && input != "4");

					chooseSpecialAction(players.at(i), stoi(input), turnTaker);

					std::cout << "\n~ Your current location is: " << players.at(i)->getLocation()->toString() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
					std::cout << "~ Actions left: " << players.at(i)->getActions() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
				}
				else if( input == "3") {
					do
					{
						std::cout << "\t~ ROLE ACTION ~" << std::endl;
                        if(canGetResearcherCard) {
                            std::cout << "1 - To get a card from Researcher" << std::endl;
                        }
                        if(players.at(i)->getRoleSave()->getName() == "Researcher") {
							std::cout << "1 - " << players.at(i)->getRoleSave()->getDescription() << std::endl;
						} else if(players.at(i)->getRoleSave()->getName() == "Dispatcher") {
							std::cout << "2 - " << players.at(i)->getRoleSave()->getDescription() << std::endl;
						} else if(players.at(i)->getRoleSave()->getName() == "Operations Expert") {
							std::cout << "3 - " << players.at(i)->getRoleSave()->getDescription() << std::endl;
						} else if(players.at(i)->getRoleSave()->getName() == "Contigency Planner" && !playerDiscard.isEmpty()) {
							std::cout << "4 - " << players.at(i)->getRoleSave()->getDescription() << std::endl;
						}

						std::cout << "\n\t0 - BACK" << std::endl;

						input.clear();

						std::cout << "> ";
						std::cin >> input;

						if (input == "menu" || input == "details" || input == "map" || input == "board" || input == "help")
						{
							helpMenu(input);
							//system("PAUSE");
						}

						if (input == "0")
							goto chooseAction; //HACKS

					} while (input != "1" && input != "2" && input != "3" && input != "4");

					roleActions(players.at(i), stoi(input), turnTaker, canGetResearcherCard);

					std::cout << "\n~ Your current location is: " << players.at(i)->getLocation()->toString() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
					std::cout << "~ Actions left: " << players.at(i)->getActions() << std::endl;
					std::cout << "--------------------------------------------------" << std::endl;
				}
			}

			//==============================================================================================TODO Extract to separate method

            //***** DRAW 2 PLAYER CARDS *****
            std::cout << "\n~ Drawing two Player Cards for Player " << i + 1 << " [" << players.at(i)->getName() << "]..." << std::endl;
            for (int j = 0; j < 2; j++) //Draw 2 Player Cards
            {
                Card* card = playerDeck.drawBack();
                if (card->getType() == CardType::EPIDEMIC){
                    playerDiscard.add(card);
                    std::cout << players.at(i)->getName() << " has drawn an epidemic card!\n";
                    Card* cityToInfect = infectionDeck.drawBack();
                    std::cout << "\tCity to infect : " <<cityToInfect->getName() << std::endl;
                    for(Vertex* v : map.getVertexList()) {
                        if(v->getName() == cityToInfect->getName()) {
                            infection.infectEpidemic(board, dynamic_cast<CityVertex*>(v),players,map,NULL);
                        }
                    }
                    infectionDiscard.shuffle();
                    for (auto a: infectionDiscard.getCardsInDeck()){
                        infectionDeck.addToFront(a);
                    }
                }
                else {
                    std::cout<< players.at(i)->getName() << " drew " << card->getName() <<" \n";
                    players.at(i)->addToHand(card); //Keep the card if it's not an Epidemic Card
                    std::cout <<"\tYou now have " << players.at(i)->getHand().size() << " cards\n";
                }
            }

            if (players.at(i)->getHand().size() >= MAX_CARDS)
            {
                discardCard(players.at(i));
            }
            std::cout<<"Player will now infect " << board.getInfectionRate() << " cities.\n";
            for (int p=0;p<board.getInfectionRate();p++){
                Card* cityToInfect = infectionDeck.drawFront();
                std::cout << "City to infect : " <<cityToInfect->getName() << std::endl;
                for(Vertex* v : map.getVertexList()) {
                    if(v->getName() == cityToInfect->getName()) {
                        infection.infectCity(board,dynamic_cast<CityVertex*>(v),1,players,map,NULL);
                    }
                }

            }


		}
	}
}



void Game::save() {
	SaveLoadDirector cook;
	GameBuilder* save = new SaveGameBuilder(this);

	cook.setGameBuilder(save);
	cook.saveGame();
}

void Game::load() {
    SaveLoadDirector cook;
    GameBuilder* load = new LoadGameBuilder(this);

    cook.setGameBuilder(load);
    cook.constructGame();
}

void Game::run()
{
	start();
    configure();
	play();
}