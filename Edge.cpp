#include "Edge.h"
#include <string>

//Edge::Edge()
//{
//}

Edge::~Edge()
{
}

bool Edge::contains(Vertex* v)
{
	if (*v == *v1 || *v == *v2)
		return true;
	return false;
}

bool Edge::operator==(Edge e) const
{
	if (*v1 == *e.v1 && *v2 == *e.v2)
		return true;
	return false;
}
