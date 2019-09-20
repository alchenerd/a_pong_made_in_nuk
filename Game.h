#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "Ball.h"
#include "Board.h"
#include "Wall.h"
#include "Ball.h"
#include "Boundary.h"
using namespace std;

class Game
{		
private:
	Ball NowBall;
	Board Player1, Player2;
	Wall UpWall, DownWall;
	Boundary LeftBound, RightBound;
	bool isPause;
	bool isCounting;
	bool isEnd;	
	int GameStatus;//0 = gaming 1 = p1 win, 2 = p2 win, 3 = pause 4 = countdown"3" 5 = countdown"2" 6 = countdown"1"
	static int CountdownPauseFrame;
public:
	Game();
	void ResetGame();
	void Calculate(unsigned int);

	void pmove();
	void bmove();

	void collision();

	int getLscore()const;
	int getRscore()const;

	bool getIsPause()const;
	void changePause();

	bool getIsCounting()const;
	void changeCounting();

	void setGameStatus(int);
	int getGameStatus()const;

	const Ball& getBallRef() const;
	const Board& getP1Ref() const;
	const Board& getP2Ref() const;
	const Wall& getWallURef() const;
	const Wall& getWallDRef() const;
	const Boundary& getLBRef() const;
	const Boundary& getRBRef() const;

	static void setCountdownPauseFrame(int);
	static int getCountdownPauseFrame();

	void checkBallAndBoard();
};

#endif