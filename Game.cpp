#include "stdafx.h"
#include <windows.h>
#include "Game.h"
#include "Ball.h"
#include "Board.h"
#include "Wall.h"
#include "Boundary.h"
#include "vCanvas.h"

/*private:
	Ball NowBall;
	Board Player1, Player2;
	Wall UpWall, DownWall;
	Boundary LeftBound, RightBound;
	bool isPause;
	bool isCounting;
	bool isEnd;	
	int GameStatus;//0 = gaming 1 = p1 win, 2 = p2 win, 3 = pause 4 = countdown"3" 5 = countdown"2" 6 = countdown"1"
	static int CountdownPauseFrame;
*/

int Game::CountdownPauseFrame = 64;

Game::Game()
{
	ResetGame();
}
void Game::ResetGame()
{
	NowBall.setBall(true);//reset ball;
	LeftBound.resetPoint();//reset point;
	Player1.setPosition(true);//reset player position
	Player2.setPosition(false);
	UpWall.setPosition(true);//reset wall position
	DownWall.setPosition(false);
	LeftBound.setPosition(true);//reset boundary position
	RightBound.setPosition(false);
	isPause = false;
	isCounting = true;
	isEnd = false;
	Board::setCountDown(0);
	setGameStatus(4);
	Beep(1046,2000/64);
}
void Game::Calculate(unsigned int keycode)
{
	if(keycode == 13&&!getIsCounting())//enter
	{
		changePause();
		if(getIsPause())
		{
			Beep(1046,100);
			Beep(784,100);
			Beep(1046,100);
			Beep(784,100);
			setGameStatus(3);
		}
		else if(getGameStatus() == 1 || getGameStatus() == 2)
			ResetGame();
		else
			setGameStatus(0);
	}
	if(!getIsPause())
	{
		if(keycode == 87)//W
		{
			Player1.setIsUp(true);
		}
		else if(keycode == 83)//S
		{
			Player1.setIsDown(true);
		}
		else if(keycode == 38)//UP
		{
			Player2.setIsUp(true);
		}
		else if(keycode == 40)//DOWN
		{
			Player2.setIsDown(true);
		}
	}
}
void Game::pmove()
{
	if(!getIsPause())
	{
		if(Player1.getDelay() == 0)
		{
			Player1.move();
			Player2.move();
			Player1.setDelay(1);
		}
		else
		{
			Player1.setDelay(Player1.getDelay()-1);
		}
	}
}
void Game::bmove()
{
	if(!getIsPause()&&!isCounting)
	{
		if(NowBall.getDelay() == 0)
		{
			//move ball
			NowBall.move();	
			NowBall.setDelay(NowBall.getMaxDelay());
			
			//determine score up
			int LeftP = Boundary::getLpoint();
			int RightP = Boundary::getRpoint();
			RightBound.collision(NowBall);
			LeftBound.collision(NowBall);
			if(LeftP!=Boundary::getLpoint()||RightP!=Boundary::getRpoint())
			{
				Board::setCountDown(0);
				changeCounting();
				setGameStatus(4);
				Beep(1046,2000/64);
			}
		}
		else
		{
			NowBall.setDelay(NowBall.getDelay()-1);
		}
		if(Boundary::getLpoint() == 7 || Boundary::getRpoint() == 7)
		{
			if(Boundary::getLpoint()>Boundary::getRpoint())
			{
				ResetGame();
				setGameStatus(1);
			}
			else if(Boundary::getLpoint()<Boundary::getRpoint())
			{
				ResetGame();
				setGameStatus(2);
			}			
			Beep(523,100);
			Beep(659,100);
			Beep(784,100);
			Beep(1046,300);
		}
	}
}

void Game::collision()
{
	if(!getIsPause()&&!isCounting)
	{
		if(NowBall.getDelay() == 0)
		{
			//polymorphism here
			//determine ball direction

			Player2.collision(NowBall);
			Player1.collision(NowBall);

			UpWall.collision(NowBall);
			DownWall.collision(NowBall);
		}
	}
}

int Game::getLscore()const
{
	return Boundary::getLpoint();
}
int Game::getRscore()const
{
	return Boundary::getRpoint();
}

bool Game::getIsPause()const
{
	return isPause;
}
void Game::changePause()
{
	isPause = !isPause;
}

bool Game::getIsCounting()const
{
	return isCounting;
}
void Game::changeCounting()
{
	isCounting = !isCounting;
}

void Game::setGameStatus(int stat)
{
	GameStatus = stat;
}
int Game::getGameStatus()const
{
	return GameStatus;
}

const Ball& Game::getBallRef() const
{return NowBall;}
const Board& Game::getP1Ref() const
{return Player1;}
const Board& Game::getP2Ref() const
{return Player2;}
const Wall& Game::getWallURef() const
{return UpWall;}
const Wall& Game::getWallDRef() const
{return DownWall;}
const Boundary& Game::getLBRef() const
{return LeftBound;}
const Boundary& Game::getRBRef() const
{return RightBound;}

void Game::setCountdownPauseFrame(int frame)
{
	CountdownPauseFrame = frame;
}

int Game::getCountdownPauseFrame()
{
	return CountdownPauseFrame;
}

void Game::checkBallAndBoard()
{
	if(NowBall.getxpos() == Player1.getX())
	{
		if(NowBall.getypos() == Player1.getYUpEnd())//if the ball is inside the board(up)
		{
			NowBall.adjustYPosition(Player1.getYUpEnd()-1);
		}

		if(NowBall.getypos() == Player1.getYDownEnd() )//if the ball is inside the board(down)
		{
			NowBall.adjustYPosition(Player1.getYDownEnd()+1);
		}
	}

	if(NowBall.getxpos() == Player2.getX())
	{
		if(NowBall.getypos() == Player2.getYUpEnd())//if the ball is inside the board(up)
		{
			NowBall.adjustYPosition(Player2.getYUpEnd()-1);
		}

		if(NowBall.getypos() == Player2.getYDownEnd() )//if the ball is inside the board(down)
		{
			NowBall.adjustYPosition(Player2.getYDownEnd()+1);
		}
	}
}