#include "Tetrominos.h"
#include "Constants.h"

void Tetrominos::move(bool *key, bool &rotateHold)
{
	m_currentX += (key[0] && Fits(INCREMENT_X)) ? 1 : 0;
	m_currentX -= (key[1] && Fits(DECREMENT_X)) ? 1 : 0;
	m_currentY += (key[2] && Fits(INCREMENT_Y)) ? 1 : 0;

	if (key[3])	//check if we are holding the key
	{				//and whether we have been holding it down since last loop
		m_currentRotation += (!rotateHold && Fits(INCREMENT_ROT)) ? 1 : 0;
		rotateHold = true;
	}
	else
	{
		rotateHold = false;
	}
}

bool Tetrominos::Fits(Increment inc)	//check if we can move the piece into it's next position before moving it
{
	int nextX = m_currentX; int nextY = m_currentY; int nextRotation = m_currentRotation;	//make some temporary variables to hold the next position
	switch (inc)
	{
	case DO_NOTHING:		nextX = m_currentX;						break;
	case INCREMENT_X:		nextX = m_currentX + 1;					break;
	case DECREMENT_X:		nextX = m_currentX - 1;					break;
	case INCREMENT_Y:		nextY = m_currentY + 1;					break;
	case INCREMENT_ROT:		nextRotation = m_currentRotation + 1;	break;
	default:				nextX = m_currentX;
	}

	for (int px = 0; px < 4; ++px)
		for (int py = 0; py < 4; ++py)
		{
			//iterate across tetromino and get index into piece
			int pi = Rotate(px, py, nextRotation);
			int fi = (nextY + py) * nFieldWidth + (nextX + px);

			if (nextX + px >= 0 && nextX + px < nFieldWidth)
			{
				if (nextY + py >= 0 && nextY + py < nFieldHeight)
				{
					if (Tetrominos::tetrominos[m_currentPiece][pi] == L'X' && pField[fi] != 0)
						return false;
				}
			}
		}
	return true;	//if anything fails then the function just quits.. default is return true
}

void Tetrominos::lockPiece()
{
	//iterate through the 16 tiles that the piece is in and if we have an 'X' then set the pField value to m_currentPiece + 1
	for (int px = 0; px < 4; ++px)
		for (int py = 0; py < 4; ++py)
			if (tetrominos[m_currentPiece][Rotate(px, py, m_currentRotation)] == L'X')
				pField[(m_currentY + py)*nFieldWidth + (m_currentX + px)] = m_currentPiece + 1;
}

void Tetrominos::checkForLines()
{
	//check have we got any lines (only need to check where the last piece landed)
	for (int py = 0; py < 4; ++py)
		if (m_currentY + py < nFieldHeight - 1)	//boundary check
		{
			bool bLine = true;
			for (int px = 1; px < nFieldWidth - 1; ++px)
				bLine &= (pField[(m_currentY + py) * nFieldWidth + px]) != 0;

			if (bLine)
			{
				//remove line & set to =
				for (int px = 1; px < nFieldWidth - 1; ++px)
					pField[(m_currentY + py) * nFieldWidth + px] = 8;
				m_lines.push_back(m_currentY + py);
			}
		}
}

void Tetrominos::increaseScoreAndSpeed()
{
	m_pieceCount++;		//how many tetrominos have we had already?
	if (m_pieceCount % 10 == 0)	//if it is 10 and the speed is still greater than 20, increase the speed
		if (m_ticksBeforeDown >= 10) m_ticksBeforeDown--;	//speed is the count of number of game loops we go through to force down

	m_score += 25;	//increase score for each piece
	if (!m_lines.empty()) m_score += (1 << m_lines.size()) * 100;	//increase score if we get a line
}

void Tetrominos::chooseNextPiece()
{
	//choose next piece
	m_currentX = nFieldWidth / 2;
	m_currentY = 0;
	m_currentRotation = 0;
	m_currentPiece = rand() % 7;
}