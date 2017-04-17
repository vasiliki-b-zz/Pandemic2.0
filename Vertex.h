#pragma once

#include <string>

class Vertex
{
public:
	//Vertex();
	~Vertex();
	Vertex(std::string name, int value) { this->name = name; this->value = value; };
	bool operator==(Vertex v) const;
	bool operator<(Vertex v) const;
	std::string getName() const { return name; };
	int getValue() const { return value; };
	virtual std::string toString();

private:
	std::string name;
	int value;
};

