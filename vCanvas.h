//參考http://benryves.com/tutorials/winconsole/ 及 遊戲程式設計概論的"虛擬畫布"部分

#ifndef _vCANVAS_H_
#define _vCANVAS_H_

#include <windows.h>
#include "Ball.h"
#include "Board.h"
#include "Wall.h"
#include "Boundary.h"
#include "Game.h"

#define ConsoleBufferWidth 120//must can be divided by 4 and should be greater than 80
#define ConsoleBufferHeight 25//should be 25
#define LConsoleMidPoint (ConsoleBufferWidth/2)
#define RConsoleMidPoint (ConsoleBufferWidth/2+1)

extern HANDLE wHnd;		// Handle to write to the console.
extern HANDLE rHnd;		// Handle to read from the console.


class cl_vCanvas
{
	friend ostream& operator<< (ostream&, const cl_vCanvas&);
private:
	CHAR_INFO VirtualCanvas[ConsoleBufferWidth*ConsoleBufferHeight];
public:
	cl_vCanvas();
	void setWindow( void );	//get handles ready here too;
	void PrinttoConsole( void ) const;
	void ClearCanvas( void );
	void WriteCanvas(const Ball&, cl_vCanvas&);
	void WriteCanvas(const Board&, cl_vCanvas&);
	void WriteCanvas(const Wall&, cl_vCanvas&);
	void WriteCanvas(const Boundary&, cl_vCanvas&);
	void WriteCanvas(Game&, cl_vCanvas&);
};

/*
// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	
	SetConsoleTitle(TEXT("PONG"));

	// Set up the required window size:
    SMALL_RECT windowSize = {0, 0, ConsoleBufferWidth-1, ConsoleBufferHeight-1};

    // Change the console window size:
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	    // Create a COORD to hold the buffer size:
    COORD bufferSize = {ConsoleBufferWidth, ConsoleBufferHeight};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(wHnd, bufferSize);
	
	getch();
*/

#endif