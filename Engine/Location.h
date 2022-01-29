#pragma once

struct Location
{
	Location Add(Location loc, Location delta_loc);
	int x;
	int y;
};