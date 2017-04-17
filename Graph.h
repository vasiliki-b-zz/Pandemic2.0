#pragma once

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "Edge.h"

class Graph
{
public:
	Graph();
	~Graph();
	int size();

	bool containsVertex(Vertex* v);
	bool containsEdge(Edge e);
	void add(Vertex* v);
	void remove(Vertex* v);
	void addEdge(Vertex* v1, Vertex* v2);
	void removeEdge(Vertex* v1, Vertex* v2);
	void setNodes(std::vector<Vertex*> v) { this->vertexList = v;};
	void setEdges(std::vector<Edge> edges) { this->edgeList = edges;};
	Vertex* getVertex(Vertex* v) const;
	Vertex* getVertex(std::string name) const; //Pre-condition: No duplicate vertex names allowed
	int save(std::ofstream &file);
	Graph load(std::ifstream &file);
	void loadMap(std::ifstream &file);
	std::vector<Vertex*> getNeighbours(Vertex* v); //const?
	std::vector<Vertex*> getVertexList() const;
	std::vector<Edge> getEdgeList() {return this->edgeList;};
	std::string toString();
	void updateRSInEdge(std::string);
	void updateDSInEdge(std::string, int);

private:
	std::vector<Vertex*> vertexList;
	std::vector<Edge> edgeList;
	void sortByValue();
};

struct CompareByValue 
{
	bool operator()(Vertex* v1, Vertex* v2) { return *v1 < *v2; };
};



