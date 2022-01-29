#include "CellsBoard.h"
#include "Board.h"

void CellsBoard::Cell::Update(Board& brd, Graphics& gfx) const
{
	if (isActive == true)
	{
		brd.DrawCell(loc, gfx);
	}
}

void CellsBoard::Cell::Activate()
{
	isActive = true;
}

void CellsBoard::Cell::Deactivate()
{
	isActive = false;
}

Location CellsBoard::Cell::GetLoc()
{
	return loc;
}

void CellsBoard::Cell::SetLoc(Location in_loc)
{
	loc = in_loc;
}

bool CellsBoard::Cell::GetIsActive()
{
	return isActive;
}

void CellsBoard::CellInit(int i)
{
	const int x_pos = i % Board::width;

	// determine whether a layer is fully initialised
	if (x_pos == 0 && i != 0)
	{
		if (init_layer < Board::width - 1)
		{
			++init_layer;
		}
	}
	Location newLoc = {x_pos, init_layer};
	cells[i].SetLoc(newLoc);
}

void CellsBoard::Update(Keyboard& kbd, Mouse& mouse, Board& brd, Graphics& gfx)
{
	turnInterval -= ft.Mark();

	if (kbd.KeyIsPressed('1'))
	{
		maxTurnInterval = 0.5f;
	}
	if (kbd.KeyIsPressed('2'))
	{
		maxTurnInterval = 0.3f;
	}
	if (kbd.KeyIsPressed('3'))
	{
		maxTurnInterval = 0.2f;
	}
	if (kbd.KeyIsPressed('4'))
	{
		maxTurnInterval = 0.1f;
	}
	if (kbd.KeyIsPressed('5'))
	{
		maxTurnInterval = 0.06f;
	}

	if (turnInterval <= 0)
	{
		for (int i = 0; i < Board::nCells; ++i)
		{
			if (isSimulating)
			{
				int neighbours = CellCheck(CellToLocation(i));
				if (neighbours < 2 || neighbours > 3)
				{
					deactivate_queue[i] = 1;
				}
				if (neighbours == 3)
				{
					activate_queue[i] = 1;
				}
			}
		}
		turnInterval = maxTurnInterval;
	}

	for (int i = 0; i < Board::nCells; ++i)
	{
		if (deactivate_queue[i] == 1)
		{
			cells[i].Deactivate();
			deactivate_queue[i] = 0;
		}
	}

	for (int i = 0; i < Board::nCells; ++i)
	{
		if (activate_queue[i] == 1)
		{
			cells[i].Activate();
			activate_queue[i] = 0;
		}
	}

	// update individual cells
	for (int i = 0; i < Board::nCells; ++i)
	{
		cells[i].Update(brd, gfx);
	}


	if (kbd.KeyIsPressed(VK_RETURN) && mouseDbn == false)
	{
		if (isSimulating == true)
		{
			isSimulating = false;
		}
		else
		{
			isSimulating = true;
		} 
		mouseDbn = true; 
	}
	if (!(kbd.KeyIsPressed(VK_RETURN)))
	{
		mouseDbn = false;
	}

	if (mouse.LeftIsPressed())
	{
		int xPos = mouse.GetPosX() / Board::dimension;
		int yPos = mouse.GetPosY() / Board::dimension;
		
		cells[LocationToCell({xPos, yPos})].Activate();
	}
}

int CellsBoard::CellCheck(Location loc)
{
	int neighbours = 0;
	
	if (loc.y == 0 || loc.y == 59 || loc.x == 0 || loc.x == 79) 
	{
		return 0;
	}

	int up = LocationToCell(loc.Add(loc, { 0, -1 }));
	int down = LocationToCell(loc.Add(loc, { 0, 1 }));
	int left = LocationToCell(loc.Add(loc, { -1, 0 }));
	int right = LocationToCell(loc.Add(loc, { 1, 0 }));

	int up_right = LocationToCell(loc.Add(loc, { 1, -1 }));
	int up_left = LocationToCell(loc.Add(loc, { -1, -1 }));
	int down_right = LocationToCell(loc.Add(loc, { 1, 1 }));
	int down_left = LocationToCell(loc.Add(loc, { -1, 1 }));

	if (cells[up].GetIsActive())
	{
		neighbours++;
	}
	if (cells[down].GetIsActive())
	{
		neighbours++;
	}
	if (cells[left].GetIsActive())
	{
		neighbours++;
	}
	if (cells[right].GetIsActive())
	{
		neighbours++;
	}
	if (cells[up_right].GetIsActive())
	{
		neighbours++;
	}
	if (cells[up_left].GetIsActive())
	{
		neighbours++;
	}
	if (cells[down_right].GetIsActive())
	{
		neighbours++;
	}
	if (cells[down_left].GetIsActive())
	{
		neighbours++;
	}

	// returns the number of neighbours that is active
	return neighbours;
}

int CellsBoard::LocationToCell(Location in_loc)
{ 
	return in_loc.y * 80 + in_loc.x;
}


Location CellsBoard::CellToLocation(int in_celln)
{
	return cells[in_celln].GetLoc();
}

