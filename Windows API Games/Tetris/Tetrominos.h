#pragma once
#include <iostream>
#include <vector>

extern const int nFieldWidth;	//just need to forward declare this so the class definition below can use it

class Tetrominos
{
public:
	enum Increment
	{
		DO_NOTHING,
		INCREMENT_X,
		DECREMENT_X,
		INCREMENT_Y,
		INCREMENT_ROT,
		MAX_INCREMENT
	};

private:
	int m_currentPiece = 0;
	int m_currentX = nFieldWidth / 2;	//where is it located? to start its in the middle
	int m_currentY = 0;
	int m_currentRotation = 0;

	int m_pieceCount = 0;
	int m_score = 0;
	std::vector<int> m_lines;

	bool m_forceDown = true;
	int m_tickCounter = 0;
	int m_ticksBeforeDown = 20;

public:
	Tetrominos()	//default constructor, doesn't need to do anything as we have initialised all of the members non-statically already
	{
	}

	static std::wstring tetrominos[7];	//statically allocate an array of wstrings representing the tetrominos

	void move(bool *key, bool &rotateHold);	//arguments are an array whether you are holding down the key, and if you were holding it since last game loop
	bool Fits(Increment inc = DO_NOTHING);	//check if we can move the piece into it's next position before moving it
	void lockPiece();						//if cant fit then we lock the piece into position by adding it to the background
	void checkForLines();					//check if we have a full line anywhere, and change that line to '=' signs
	void increaseScoreAndSpeed();	//increase the score and the speed 
	void chooseNextPiece();					//at random, choose a new piece

	//game counters & difficulty
	void resetTicks() {	m_tickCounter = 0;	}
	bool gameTicks()
	{
		m_tickCounter++;
		return (m_tickCounter == m_ticksBeforeDown);
	}

	// Access Functions
	int getCurrentPiece() const { return m_currentPiece; }
	int getCurrentX() const { return m_currentX; }
	int getCurrentY() const {	return m_currentY;	}
	int getCurrentRotation() const { return m_currentRotation; }
	int getScore() const { return m_score; }

	std::vector<int> getLines() const { return m_lines; }
	void clearLines() { m_lines.clear(); }
	void incrementY() { m_currentY++; }
};