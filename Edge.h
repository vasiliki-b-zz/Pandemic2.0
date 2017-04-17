#pragma once
#include "CityVertex.h"

class Edge
{
public:
	Edge();
	~Edge();
	Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v2) {};
	bool contains(Vertex* v);
	bool operator==(Edge e) const;
	Vertex* getStart() const { return v1; };
	Vertex* getEnd() const { return v2; };

private:
	Vertex* v1;
	Vertex* v2;
};

