#include "Board.h"
#include <assert.h>

void Board::DrawCell(Location loc, Graphics& gfx) const
{
	assert(loc.x < width);
	assert(loc.y < height);
	gfx.DrawRect(dimension * loc.x, dimension * loc.y, dimension, dimension, Colors::Gray);
}

