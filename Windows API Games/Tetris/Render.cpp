#include "Tetrominos.h"
#include "Constants.h"
#include <Windows.h>
#include <chrono>
#include <thread>

void initialiseField()
{
	pField = new unsigned char[nFieldWidth*nFieldHeight];	//create playing field buffer
	for (int x = 0; x < nFieldWidth; ++x)					//loop through the field, if a block is at the border set it to 9 (boundary). 
		for (int y = 0; y < nFieldHeight; ++y)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;	//If not then set it to 0 (empty space)
}

void drawField(wchar_t *scrn)
{
	//Draw field with an ofset of 2 (so not right in the corner)
	//for the " ABCEDFG=#" bit... if in our field array, the index is 0, we draw " "
	//ABCEDFG represent the tetris pieces, = represents a line, # represents a border
	for (int x = 0; x < nFieldWidth; ++x)
		for (int y = 0; y < nFieldHeight; y++)
			scrn[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];	//could use a switch statement
}

void drawTetromino(wchar_t *scrn, const Tetrominos &t)
{
	//draw current piece
	for (int px = 0; px < 4; ++px)
		for (int py = 0; py < 4; ++py)
			if (Tetrominos::tetrominos[t.getCurrentPiece()][Rotate(px, py, t.getCurrentRotation())] == L'X')
				scrn[(t.getCurrentY() + py + 2)*nScreenWidth + (t.getCurrentX() + px + 2)] = t.getCurrentPiece() + 65; //add 65 to convert to A,B,C.. etc, this is ASCII code
}

void updateLines(Tetrominos &tet, wchar_t *screen, void *hConsole, unsigned long dwBytesWritten)
{
	if (!tet.getLines().empty())
	{
		// Display frame (cheekily to draw lines)
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, { 0,0 }, &dwBytesWritten);
		std::this_thread::sleep_for(std::chrono::milliseconds(400));	//delay a bit

																		//then remove the lines and move down all the pieces above the lines
		for (auto &v : tet.getLines())
			for (int px = 1; px < nFieldWidth - 1; ++px)
			{
				for (int py = v; py > 0; --py)
					pField[py*nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
				pField[px] = 0;
			}
		tet.clearLines();
	}
}
