#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <boost/foreach.hpp>

#include "Graph.h"
#include "DiseaseColour.h"
#include "Util.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

int Graph::size()
{
	return vertexList.size();
}

bool Graph::containsVertex(Vertex* v)
{
	/*for each (Vertex V in vertexList)
		if (v == V)
		{
			return true;
		}
	return false;*/

	for (int i = 0; i < vertexList.size(); i++)
	{
		if (*vertexList.at(i) == *v) {
            return true;
        }
	}
	return false;
}

bool Graph::containsEdge(Edge e)
{
	/*for each (Edge E in edgeList)
		if (e == E)
			return true;
	return false;*/

	for (int i = 0; i < edgeList.size(); i++)
	{
		if (edgeList.at(i) == e)
			return true;
	}
	return false;
}

void Graph::add(Vertex* v)
{
	if (containsVertex(v))
	{
		//std::cerr << "(!) Error: Vertex " + v.getName() + " already exists in the graph...\n" << std::endl;
		return;
	}
	vertexList.push_back(v);
	sortByValue();
}

void Graph::remove(Vertex* v)
{
	if (!containsVertex(v))
	{
		std::cerr << "(!) Error: Vertex " + v->getName() + " does not exist in the graph...\n" << std::endl;
		return;
	}

	for (int i = 0; i < vertexList.size(); i++)
	{
		if (&vertexList.at(i) == &v)
		{
			vertexList.erase(vertexList.begin() + i);
			break;
		}
	}

	for (int i = 0; i < edgeList.size(); i++)
	{
		if (edgeList.at(i).contains(v))
			edgeList.erase(edgeList.begin() + i);
	}
}

void Graph::addEdge(Vertex* v1, Vertex* v2)
{
	if (!containsVertex(v1))
		vertexList.push_back(v1);
	else if (!containsVertex(v2))
		vertexList.push_back(v2);

	Edge e1 = Edge(v1, v2);
	Edge e2 = Edge(v2, v1);

	if (containsEdge(e1) | containsEdge(e2))
	{
		return;
	}

	edgeList.push_back(e1);
	edgeList.push_back(e2);
}

void Graph::removeEdge(Vertex* v1, Vertex* v2)
{
	if (!containsVertex(v1) | !containsVertex(v2))
	{
		std::cerr << "(!) Error: Cannot remove edge. One of those vertices is not in the graph...\n" << std::endl;
		return;
	}

	//for each (Edge e in edgeList) 
	//	if (e.contains(v1) && e.contains(v2))
	//		edgeList.remove(e); //ERROR!
	
	for (int i = 0; i < edgeList.size(); i++)
	{
		if (edgeList.at(i).contains(v1) && edgeList.at(i).contains(v2))
			edgeList.erase(edgeList.begin() + i);
	}
}

Vertex* Graph::getVertex(Vertex* v) const
{
	try
	{
        BOOST_FOREACH(Vertex* V, vertexList)
			if (&V == &v)
				return v;
		throw -1;
	}
	catch (int e)
	{
		std::cout << "(!) Error: That vertex could not be found in the graph..." << std::endl;
	}
}

Vertex* Graph::getVertex(std::string name) const
{
	try
	{
		BOOST_FOREACH(Vertex* v, vertexList)
			if (v->getName() == name)
				return v;
		throw -1;
	}
	catch (int e)
	{
		std::cout << "(!) Error: That vertex could not be found in the graph..." << std::endl;
	}
}

void Graph::sortByValue()
{
	std::sort(vertexList.begin(), vertexList.end(), CompareByValue());
}

int Graph::save(std::ofstream &file)
{
	if (file.is_open())
	{
		file << toString(); //Output graph to file
		file.close();
		std::cout << "(OK) File saved successfully!" << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;

	return 0;
}

void Graph::loadMap(std::ifstream &file) {

	if (file.is_open())
	{
		//try
		std::string line;
		while (std::getline(file, line)) //Read file line by line
		{
			std::vector<std::string> cityAndNeighbours;
			boost::split(cityAndNeighbours, line, boost::is_any_of(":"));
			assert(cityAndNeighbours.size() == 2);

			auto parseCityAndProps = [](std::string input) {
				std::vector<std::string> nameAndProps;
				boost::split(nameAndProps, input, boost::is_any_of("("));
				assert(nameAndProps.size() == 2);

				return nameAndProps;
			};

			auto cleanParams = [](std::string input) {
				return input.replace(input.find(")"), 1, "");
			};

			auto parseParams = [](std::string input) {
				std::vector<std::string> params;
				boost::split(params, input, boost::is_any_of(","));
				assert(params.size() == 3);
				return params;
			};

			auto nameAndProps = parseCityAndProps(cityAndNeighbours[0]);
			auto cityName = nameAndProps[0];
			auto params = parseParams(cleanParams(nameAndProps[1]));
			auto color = params[0];
			auto dCubes = std::stoi(params[1]);
			auto rStations = (bool) std::stoi(params[2]);
            CityVertex *cv;

			City city = City(cityName, DiseaseColourStringToEnum(color));
            for(Vertex* v : this->getVertexList()) {
                if(v->getName() == cityName) {
                    cv = dynamic_cast<CityVertex* >(v);
                    goto addNeighbours;
                }
            }

            for(Edge edge : this->getEdgeList()) {
                if(edge.getStart()->getName() == cityName) {
                    this->add(edge.getStart());
                    cv = dynamic_cast<CityVertex*>(edge.getStart());
                    goto addNeighbours;
                } else if (edge.getEnd()->getName() == cityName) {
                    this->add(edge.getEnd());
                    cv = dynamic_cast<CityVertex*>(edge.getEnd());
                    goto addNeighbours;
                }
            }
			cv = new CityVertex(city); //Create vertex with vName and vColour
			cv->addDiseaseCubes(dCubes);
			if (rStations) {
				cv->addResearchStation();
			} else {
				cv->removeResearchStation();
			}
			this->add(dynamic_cast<Vertex *>(cv));

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
                    auto neighborNameAndProps = parseCityAndProps(neighbour);
                    auto neighborCityName = neighborNameAndProps[0];
                    auto neighborParams = parseParams(neighborNameAndProps[1]);
                    auto neighborColor = neighborParams[0];
                    auto neighborDCubes = std::stoi(neighborParams[1]);
                    auto neighborRStations = (bool) std::stoi(neighborParams[2]);
                    bool go = false;

                    for(Vertex* isInList: this->getVertexList()) {
                        if (isInList->getName() == neighborCityName) {
                            this->addEdge(dynamic_cast<Vertex *>(cv), isInList);
                            go = true;
                            break;
                        }
                    }

                    if(!go) {
                        City neighborCity = City(neighborCityName, DiseaseColourStringToEnum(neighborColor));
                        CityVertex *edge = new CityVertex(neighborCity); //Create vertex with vName and vColour
                        edge->addDiseaseCubes(neighborDCubes);
                        if (neighborRStations) {
                            edge->addResearchStation();
                        } else {
                            edge->removeResearchStation();
                        }
                        this->addEdge(dynamic_cast<Vertex *>(cv), dynamic_cast<Vertex *>(edge));
                    }
                }
		}

		file.close();
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;
}

Graph Graph::load(std::ifstream &file)
{
	Graph graph = Graph();

	if (file.is_open())
	{
		//try
		std::string line;
		while (std::getline(file, line)) //Read file line by line
		{
			std::istringstream in_stream(line);
			std::string key, value;

			if (std::getline(in_stream, key, ':'))
			{
				std::string name, value;
				name = key.substr(0, key.find("(")); //Extract vertex name from key

				int start = key.find("(") + 1;
				int end = key.find(")") - start;

				value = key.substr(start, end); //Extract vertex colour from key



				Vertex* v = new Vertex(name, std::stoi(value.c_str()));

				graph.add(v);

				if (std::getline(in_stream, value))
				{
					start = value.find("{") + 1;
					end = value.find("}") - start;

					value = value.substr(start, end);

					int pos = 0;
					while (((pos = value.find(")")) <= (int)value.size()) && value.size() > 1)
					{
						std::string neighbour(""), nName(""), nValue("");
						neighbour = value.substr(0, pos + 1);
						value.erase(0, pos + 1);
						trim(neighbour); //Trim leading and trailing whitespace

						nName = neighbour.substr(0, neighbour.find("("));

						start = neighbour.find("(") + 1;
						end = neighbour.find(")") - start;

						nValue = neighbour.substr(start, end);

						Vertex* n = new Vertex(nName, std::stoi(nValue.c_str()));

						graph.addEdge(v, n);

						delete n;
					}
				}
				delete v;
			}
		}
		file.close();
		std::cout << graph.toString() << std::endl;
	}
	else
		std::cout << "(!) Error: IO exception..." << std::endl;

	return graph;
}

std::vector<Vertex*> Graph::getNeighbours(Vertex* v)
{
	std::vector<Vertex*> neighbours;

	if (!containsVertex(v))
	{
		std::cerr << "(!) Error: That vertex is not in the graph...\n" << std::endl;
		return neighbours;
	}

	for (int i = 0; i < edgeList.size(); i++)
	{
		if (edgeList.at(i).contains(v)) {
            if (*edgeList.at(i).getStart() == *v) {
                neighbours.push_back(edgeList.at(i).getEnd());
            }
        }
	}
	return neighbours;
}

std::vector<Vertex*> Graph::getVertexList() const
{
	return vertexList;
}

void Graph::updateRSInEdge(std::string name) {
    for(int i = 0; i < this->getEdgeList().size(); i++) {
        if (this->getEdgeList().at(i).getStart()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->hasResearchStation() == false) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->addResearchStation();
        } else if(this->getEdgeList().at(i).getEnd()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->hasResearchStation() == false) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->addResearchStation();
        }
    }
}

void Graph::updateDSInEdge(std::string name, int number) {
    for(int i = 0; i < this->getEdgeList().size(); i++) {
        if(this->getEdgeList().at(i).getStart()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->getDiseaseCubes() == 0) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->addDiseaseCubes(number);
        } else if(this->getEdgeList().at(i).getEnd()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->getDiseaseCubes() == 0) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->addDiseaseCubes(number);
        } else if(this->getEdgeList().at(i).getStart()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->getDiseaseCubes() != 0 && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->getDiseaseCubes() != number) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->addDiseaseCubes(dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getStart())->getDiseaseCubes() + number);
        } else if(this->getEdgeList().at(i).getEnd()->getName() == name && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->getDiseaseCubes() != 0 && dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->getDiseaseCubes() != number) {
            dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->addDiseaseCubes(dynamic_cast<CityVertex*>(this->getEdgeList().at(i).getEnd())->getDiseaseCubes() + number);
        }
    }
}

std::string Graph::toString()
{
	std::string s = "";

	for (int i = 0; i < vertexList.size(); i++)
	{
		s += vertexList.at(i)->toString() + " : { ";

		std::vector<Vertex*> neighbours = this->getNeighbours(vertexList.at(i));

		for (int j = 0; j < neighbours.size(); j++)
			s += neighbours.at(j)->toString() + " ";
		s += "}\n";
	}
	return s;
}



