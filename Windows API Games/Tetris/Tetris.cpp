#include "Tetrominos.h"
#include "Constants.h"
#include <stdio.h>
#include <Windows.h>
#include <thread>
#include <vector>
#include <chrono>

//definitions with external linkage
extern const int nScreenWidth = 120;		//console screen size X (columns) //80 is standard? change this around until it works
extern const int nScreenHeight = 30;		//console screen size Y (rows)
extern const int nFieldWidth = 12;
extern const int nFieldHeight = 18;
extern unsigned char *pField = nullptr;		//dynamically allocate the map

std::wstring Tetrominos::tetrominos[7] =	//static array definition
{
	L"..X."		//shape [0]
	L"..X."
	L"..X."
	L"..X.",

	L"..X."		//shape [1]
	L".XX."
	L".X.."
	L"....",

	L".X.."		//shape[2]
	L".XX."
	L"..X."
	L"....",

	L"...."		//shape[3]
	L".XX."
	L".XX."
	L"....",

	L"..X."		//shape[4]
	L".XX."
	L"..X."
	L"....",

	L"...."		//shape[5]
	L".XX."
	L"..X."
	L"..X.",

	L"...."		//shape[6]
	L".XX."
	L".X.."
	L".X.."
};

int main()
{
	//set up our command prompt, creates an array of wchar_t's for the screen width and screen height. fills the screen with "blank stuff". 
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';

	//grabs a "handle" to the console buffer, and sets it as the active screen buffer. Handle is a void pointer, so it can point to any type, but doenst know what that is
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	initialiseField();	//set up the boundaries... note that this does not write to screen

	bool bKey[4];
	bool bRotateHold = false;

	bool bGameOver = false;
	bool bForceDown = true;
	Tetrominos tet;	//tet is the current tetromino, when the tetromino is locked, tet becomes the new tetromino
					//at the top of the screen... so tet is never destroyed & recreated, only reset (by chooseNextPiece())

	while (!bGameOver)
	{
		// TIMING	======================================================================================
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		bForceDown = tet.gameTicks();

		// INPUTS	======================================================================================
		for (int k = 0; k < 4; ++k)											// R   L   D Z
			bKey[k] = (0x8000 & GetAsyncKeyState(static_cast<unsigned char>("\x27\x25\x28Z"[k]))) != 0;
		//uses const char string for the hexidecimals for right, left, down and Z key. Returns true if any of them
		//are being pressed. GetAsyncKeyState is from windows


		// GAME LOGIC	===================================================================================
		//Shapes falling, collision detection, scoring
		tet.move(bKey, bRotateHold);
		if(bForceDown)
		{
			if (tet.Fits(Tetrominos::INCREMENT_Y))	//dont need Increment::
				tet.incrementY(); //it can, so do it!
			else
			{
				tet.lockPiece();	//adds the piece to pField
				tet.checkForLines();
				tet.increaseScoreAndSpeed();
				tet.chooseNextPiece();
				bGameOver = !tet.Fits(Tetrominos::DO_NOTHING);
			}
			tet.resetTicks();
		}


		// RENDER GAME	=====================================================================================

		//fill the values of screen with what we want so that we can draw it with writeConsoleOutputCharacter
		drawField(screen);
		drawTetromino(screen, tet);

		//Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", tet.getScore());
		//Animate the lines being removed
		updateLines(tet, screen, hConsole, dwBytesWritten);
		//Draw the final console
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}

