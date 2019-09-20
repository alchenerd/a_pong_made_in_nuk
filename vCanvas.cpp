#include "stdafx.h"
#include <windows.h>
#include "vCanvas.h"
#include "Ball.h"
#include "Board.h"
#include "Wall.h"
#include "Boundary.h"
#include <iostream>

using namespace std;

//	CHAR_INFO VirtualCanvas[ConsoleBufferWidth][ConsoleBufferHeight];
ostream& operator<< (ostream& Output, const cl_vCanvas& Canvas)
{
	Canvas.PrinttoConsole();
	return Output;
}
cl_vCanvas::cl_vCanvas()
{
	setWindow();
	ClearCanvas();
}

void cl_vCanvas::setWindow( void )	//get handles ready here too;
{
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

	// Create a cursor info to hide cursor:
	CONSOLE_CURSOR_INFO CursorInfo = {1,FALSE};

	// Hide cursor
	SetConsoleCursorInfo(wHnd, &CursorInfo);

}
void cl_vCanvas::PrinttoConsole( void )const
{
	COORD BufferSize = {ConsoleBufferWidth, ConsoleBufferHeight};
	COORD StartPoint = {0,0};
	SMALL_RECT WriteArea = {0,0,ConsoleBufferWidth-1,ConsoleBufferHeight-1};
	WriteConsoleOutputA(wHnd, VirtualCanvas, BufferSize, StartPoint, &WriteArea);

}
void cl_vCanvas::ClearCanvas( void )
{
	// Clear the VirtualCanvas buffer:
	for (int i=0; i < ConsoleBufferWidth*ConsoleBufferHeight; i++)
	{
		VirtualCanvas[i].Char.AsciiChar = ' ';
		VirtualCanvas[i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
	}
}

void cl_vCanvas::WriteCanvas(const Ball& ball, cl_vCanvas& Canvas)
{
	Canvas.VirtualCanvas[ball.getxpos() + ConsoleBufferWidth * ball.getypos()].Attributes = 0 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	Canvas.VirtualCanvas[(ball.getxpos() + ConsoleBufferWidth * ball.getypos())+1].Attributes = 0 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
}
void cl_vCanvas::WriteCanvas(const Board& board, cl_vCanvas& Canvas)
{
	if(board.getIsLPlayer())
	{
		for(int i = board.getYUpEnd() ; i <= board.getYDownEnd() ; i++)
		{
			Canvas.VirtualCanvas[board.getX()+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[board.getX()+ConsoleBufferWidth*i+1].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
	}
	else
	{
		for(int i = board.getYUpEnd() ; i <= board.getYDownEnd() ; i++)
		{
			Canvas.VirtualCanvas[board.getX()+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[board.getX()+ConsoleBufferWidth*i+1].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
	}
}
void cl_vCanvas::WriteCanvas(const Wall& wall, cl_vCanvas& Canvas)
{
	for(int i = 0 ; i <= ConsoleBufferWidth-1 ; i++)
	{
		Canvas.VirtualCanvas[i+ConsoleBufferWidth*wall.getYDownEnd()].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	}
}
void cl_vCanvas::WriteCanvas(const Boundary& bound, cl_vCanvas& Canvas)
{
	switch(bound.getLpoint())
	{
	case 0:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}

	case 1:
		for(int i = LConsoleMidPoint-7; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 5; i<=8; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		break;

	case 2:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-9+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-8+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 3:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 4:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=6; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		break;

	case 5:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[LConsoleMidPoint-9+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-8+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 6:
		for(int i = LConsoleMidPoint-9; i<=LConsoleMidPoint-4; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[LConsoleMidPoint-8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[LConsoleMidPoint-5+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[LConsoleMidPoint-4+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	default:
		break;

	}
	switch(bound.getRpoint())
	{
	case 0:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}

	case 1:
		for(int i = RConsoleMidPoint+6; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 5; i<=8; i++)
		{
			Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		break;

	case 2:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+4+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+5+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 3:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 4:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=6; i++)
		{
			Canvas.VirtualCanvas[RConsoleMidPoint+4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		break;

	case 5:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+4+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+5+ConsoleBufferWidth*5].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case 6:
		for(int i = RConsoleMidPoint+4; i<=RConsoleMidPoint+9; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*4].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*6].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*8].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		for(int i = 4; i<=8; i++)
		{
			Canvas.VirtualCanvas[RConsoleMidPoint+4+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+5+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+8+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		Canvas.VirtualCanvas[RConsoleMidPoint+9+ConsoleBufferWidth*7].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	default:
		break;

	}
	for(int i = +2; i<=ConsoleBufferHeight-1-2; i+=2)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
			Canvas.VirtualCanvas[RConsoleMidPoint+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
}
void cl_vCanvas::WriteCanvas(Game& game, cl_vCanvas& Canvas)
{
	char *block;
	char *command;
	char *ptr;
	switch(game.getGameStatus())
	{
	case 0:
		break;
	case 1:
		if(!game.getIsPause())
			game.changePause();	
		if(game.getIsCounting())
			game.changeCounting();
		block =   "******************";
		command = "* Player 1 Wins! *";
		ptr = block;
		for(int i = LConsoleMidPoint-8; i <= RConsoleMidPoint+8; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}
		ptr = command;
		for(int i = LConsoleMidPoint-8; i <= RConsoleMidPoint+8; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}		
		break;
	case 2:
		if(!game.getIsPause())
			game.changePause();	
		if(game.getIsCounting())
			game.changeCounting();
		block =   "******************";
		command = "* Player 2 Wins! *";
		ptr = block;
		for(int i = LConsoleMidPoint-8; i <= RConsoleMidPoint+8; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}
		ptr = command;
		for(int i = LConsoleMidPoint-8; i <= RConsoleMidPoint+8; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}		
		break;
	case 3:
		block =   "****************";
		command = "* Game Paused. *";
		ptr = block;
		for(int i = LConsoleMidPoint-7; i <= RConsoleMidPoint+7; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*11].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*13].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}
		ptr = command;
		for(int i = LConsoleMidPoint-7; i <= RConsoleMidPoint+7; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Char.AsciiChar = *ptr;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			ptr++;
		}
		break;
	case 4:
		for(int i = 10; i<=14; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint-1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
		}
		for(int i = LConsoleMidPoint-2; i<=RConsoleMidPoint+2; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*10].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*14].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*11].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*11].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*13].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*13].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		if(game.getCountdownPauseFrame() == 0)
		{
			game.setCountdownPauseFrame(64);
			game.setGameStatus(5);
			Beep(784,2000/64);
		}
		else
		{
			game.setCountdownPauseFrame(game.getCountdownPauseFrame()-1);
		}
		break;
	case 5:
		for(int i = 10; i<=14; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint-1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
		}
		for(int i = LConsoleMidPoint-2; i<=RConsoleMidPoint+2; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*10].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*12].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*14].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
		Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*11].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*11].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[LConsoleMidPoint-2+ConsoleBufferWidth*13].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		Canvas.VirtualCanvas[LConsoleMidPoint-1+ConsoleBufferWidth*13].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		if(game.getCountdownPauseFrame() == 0)
		{
			game.setCountdownPauseFrame(64);
			game.setGameStatus(6);
			Beep(523,2000/64);
		}
		else
		{
			game.setCountdownPauseFrame(game.getCountdownPauseFrame()-1);
		}
		break;
	case 6:
		for(int i = 10; i<=14; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint-2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint-1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[LConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+1+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
			Canvas.VirtualCanvas[RConsoleMidPoint+2+ConsoleBufferWidth*i].Attributes = FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | 0;
		}
		for(int i = LConsoleMidPoint-1; i<=RConsoleMidPoint; i++)
		{
			Canvas.VirtualCanvas[i+ConsoleBufferWidth*10].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
		for(int i = 11; i<=14; i++)
		{
			Canvas.VirtualCanvas[LConsoleMidPoint+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			Canvas.VirtualCanvas[RConsoleMidPoint+ConsoleBufferWidth*i].Attributes = 0 | BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		}
		if(game.getCountdownPauseFrame() == 0)
		{
			game.setCountdownPauseFrame(64);
			game.changeCounting();
			game.setGameStatus(0);
		}
		else
		{
			game.setCountdownPauseFrame(game.getCountdownPauseFrame()-1);
		}
		break;
	default:
		break;
	}
}

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