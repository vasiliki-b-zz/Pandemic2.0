#include <iostream>
#include "DriveOrFerry.h"
#include "Game.h"

void DriveOrFerry::execute()
{
	std::cout << "\n~ Where would you like to drive/ferry?" << std::endl;

	std::vector<Vertex*> neighbours = map->getNeighbours(player->getLocation());

	for (int i = 0; i < neighbours.size(); i++)
		std::cout << "\t" << i + 1 << " - " << neighbours.at(i)->toString() << std::endl;

	int choice = Game::getUserIntput(1, neighbours.size() + 1);

	CityVertex* destination = (CityVertex*)neighbours.at(choice - 1);
	player->setLocation(destination);
}
