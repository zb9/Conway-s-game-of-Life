#include "Location.h"

Location Location::Add(Location loc, Location delta_loc)
{
	loc.x += delta_loc.x;
	loc.y += delta_loc.y;
	return { loc.x, loc.y };
}
