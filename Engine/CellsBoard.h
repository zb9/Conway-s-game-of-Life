#pragma once
#include "Location.h"
#include "Board.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "FrameTimer.h"

class CellsBoard
{
private:	
	class Cell
	{
	public:
		void Update(Board& brd, Graphics& gfx) const;
		void Activate();
		void Deactivate();

		Location GetLoc();
		void SetLoc(Location in_loc);

		bool GetIsActive();

	private:
	Location loc;
	bool isActive = false;
	
	};
public:
	void CellInit(int i);
	void Update(Keyboard& kbd, Mouse& mouse, Board& brd, Graphics& gfx);

	int CellCheck(Location loc);

	int LocationToCell(Location in_loc);
	Location CellToLocation(int in_celln);

private:
	FrameTimer ft;

	float maxTurnInterval = 0.2f;
	float turnInterval = 0.2f;

	Cell cells[Board::nCells];

	int init_layer = 0;
	int activate_queue[4800];
	int deactivate_queue[4800];

	bool isSimulating = false;
	
	bool mouseDbn = false;
};