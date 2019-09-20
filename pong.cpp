// pong.cpp : Defines the entry point for the console application.
//
//參考http://benryves.com/tutorials/winconsole/, 遊戲程式設計概論

#include "stdafx.h"
#include "myKeyboard.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <Tchar.h>
#include "vCanvas.h"

using namespace std;

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

void StartWriteCanvas(Game &game, cl_vCanvas& Canvas);

int main(int argc, _TCHAR* argv[])
{
	cl_vCanvas virCanvas;
	Game PongGame;

	//mykeyboard testing
	
	clKeyBoard Keyboard;
	unsigned int KeyCode = 0;

	while ( KeyCode != VK_ESCAPE )
	{		
		if( Keyboard.ReadKey( KeyCode ) )
		{
			PongGame.Calculate(KeyCode);
		}
		if( Keyboard.ReadKey( KeyCode ) )
		{
			PongGame.Calculate(KeyCode);
		}
		if( Keyboard.ReadKey( KeyCode ) )
		{
			PongGame.Calculate(KeyCode);
		}
		if( Keyboard.ReadKey( KeyCode ) )
		{
			PongGame.Calculate(KeyCode);
		}	
		PongGame.checkBallAndBoard();
		PongGame.pmove();
		PongGame.bmove();
		PongGame.collision();
		StartWriteCanvas(PongGame,virCanvas);
		cout<<virCanvas;
		Sleep(1000/64);
	}
	

	return 0;
}


void StartWriteCanvas(Game &game,cl_vCanvas& Canvas)
{
	Canvas.ClearCanvas();
	Canvas.WriteCanvas(game.getLBRef(), Canvas);//points and line
	Canvas.WriteCanvas(game.getWallURef(), Canvas);//wall
	Canvas.WriteCanvas(game.getWallDRef(), Canvas);
	Canvas.WriteCanvas(game.getBallRef(), Canvas);//ball
	Canvas.WriteCanvas(game.getP1Ref(), Canvas);//player1
	Canvas.WriteCanvas(game.getP2Ref(), Canvas);//player2
	Canvas.WriteCanvas(game, Canvas);//messages;
}