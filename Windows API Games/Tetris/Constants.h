#pragma once

extern const int nScreenWidth;		//console screen size X (columns) //80 is standard?
extern const int nScreenHeight;		//console screen size Y (rows)
extern const int nFieldWidth;
extern const int nFieldHeight;
extern unsigned char *pField;	//dynamically allocate the map

class Tetrominos;


int Rotate(int px, int py, int r);
void initialiseField();
void drawField(wchar_t *scrn);
void drawTetromino(wchar_t *scrn, const Tetrominos &t);
//void* == HANDLE, unsigned long == DWORD, but we can't use HANDLE or DWORD in the function decl without #including <Windows.h>
void updateLines(Tetrominos &tet, wchar_t *screen, void *hConsole, unsigned long dwBytesWritten);		
