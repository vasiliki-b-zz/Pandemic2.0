#include "Util.h"

void trim(std::string& s)
{
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);
}