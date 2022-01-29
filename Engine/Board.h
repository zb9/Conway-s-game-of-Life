#pragma once
#include "Location.h"
#include "Graphics.h"

class Board
{
public:
	void DrawCell(Location loc, Graphics& gfx) const;

private:

public:
	static constexpr int dimension = 10;
	static constexpr int width = 80;
	static constexpr int height = 60;
	static constexpr int nCells = width * height;
};