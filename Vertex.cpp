#include "Vertex.h"
//
//Vertex::Vertex()
//{
//}

Vertex::~Vertex()
{
}

bool Vertex::operator==(Vertex v) const
{
	if (name.compare(v.name) == 0) //Vertices must have unique names
		return true;
	return false;
}

bool Vertex::operator<(Vertex v) const
{
	return value < v.value;
}

std::string Vertex::toString()
{
	std::string s = "";
	s += name + "(" + std::to_string(value) + ")";
	return s;
}