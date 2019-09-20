#include "stdafx.h"
#include "Board.h"
#include "vCanvas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
private:
	int X;
	int Y_UpperEnd;//small
	int Y_LowerEnd;//big
	bool isUp;
	bool isDown;
	bool isLPlayer;
	static int Countdown;
	static int Delay;
	*/

int Board::Countdown = 0;
int Board::Delay = 0;

Board::Board(int x, int yu, int yd, bool isu, bool isd, bool isl)
:X(x), Y_UpperEnd(yu), Y_LowerEnd(yd), isUp(isu), isDown(isd), isLPlayer(isl)
{
	setPosition(isl);
}
int Board::getX() const
{
	return X;
}
int Board::getYUpEnd() const
{
	return Y_UpperEnd;
}
int Board::getYDownEnd() const
{
	return Y_LowerEnd;
}

void Board::setPosition(bool isLeft)
{
	X = (isLeft)? dLeftBoardLine:dRightBoardLine;
	Y_UpperEnd = dDefaultUend;
	Y_LowerEnd = dDefaultDend;
	isLPlayer = isLeft;
}
void Board::move()
{
	if(isUp&&isDown)
	{
		setIsUp(false);
		setIsDown(false);
	}
	else if(isUp)
	{
		if(getYUpEnd()<=2)
		{}
		else
		{
			Y_UpperEnd--;
			Y_LowerEnd--;
		}
	}
	else if(isDown)
	{
		if(getYDownEnd()>=22)
		{}
		else
		{
			Y_UpperEnd++;
			Y_LowerEnd++;
		}
	}
	setIsUp(false);
	setIsDown(false);
}
void Board::collision(Ball &ball)
{
	if(isLPlayer)
	{
		if(ball.getxpos()-getX() == 2)
		{
			if( (ball.getypos()-getYUpEnd() == -1 && ball.getIsDown()) || (ball.getypos() - getYDownEnd() == 1 && !ball.getIsDown()) )
			{
				ball.setDirection(true,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
			else if(ball.getypos() >= getYUpEnd() && ball.getypos() <= getYDownEnd() )
			{
				ball.setDirection(true,false);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
		}
		if(ball.getxpos()-getX() == 0)
		{
			if(ball.getypos()-getYUpEnd() == -1)//above
			{
				if(ball.getIsDown())
				{
					ball.setDirection(false,true);
					if(Countdown == 0)
					{
						if(ball.getMaxDelay()>1)
						{
							ball.setMaxDelay(ball.getMaxDelay()-1);
						}
						Countdown = 9;
					}
					else
					{
						Countdown--;
					}
				}
			}
			else if(ball.getypos() - getYDownEnd() == 1)//below
			{
				if(!ball.getIsDown())
				{
					ball.setDirection(false,true);
					if(Countdown == 0)
					{
						if(ball.getMaxDelay()>1)
						{
							ball.setMaxDelay(ball.getMaxDelay()-1);
						}
						Countdown = 9;
					}
					else
					{
						Countdown--;
					}
				}
			}
			else if(ball.getypos() == getYUpEnd())//if the ball is inside the board(up)
			{
				ball.adjustYPosition(getYUpEnd()-1);
				if(ball.getIsDown())
					ball.setDirection(false,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
			
			else if(ball.getypos() == getYDownEnd() )//if the ball is inside the board(down)
			{
				ball.adjustYPosition(getYDownEnd()+1);
				if(!ball.getIsDown())
					ball.setDirection(false,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
		}
	}
	else
	{
		if(getX()-ball.getxpos() == 2)
		{
			if( (ball.getypos()-getYUpEnd() == -1 && ball.getIsDown()) || (ball.getypos() - getYDownEnd() == 1 && !ball.getIsDown()) )
			{
				ball.setDirection(true,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
			else if(ball.getypos() >= getYUpEnd() && ball.getypos() <= getYDownEnd() )
			{
				ball.setDirection(true,false);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
		}
		if(ball.getxpos()-getX() == 0)
		{
			if(ball.getypos()-getYUpEnd() == -1)//above
			{
				if(ball.getIsDown())
				{
					ball.setDirection(false,true);
					if(Countdown == 0)
					{
						if(ball.getMaxDelay()>1)
						{
							ball.setMaxDelay(ball.getMaxDelay()-1);
						}
						Countdown = 9;
					}
					else
					{
						Countdown--;
					}
				}
			}
			else if(ball.getypos() - getYDownEnd() == 1)//below
			{
				if(!ball.getIsDown())
				{
					ball.setDirection(false,true);
					if(Countdown == 0)
					{
						if(ball.getMaxDelay()>1)
						{
							ball.setMaxDelay(ball.getMaxDelay()-1);
						}
						Countdown = 9;
					}
					else
					{
						Countdown--;
					}
				}
			}
			else if(ball.getypos() == getYUpEnd())//if the ball is inside the board(up)
			{
				ball.adjustYPosition(getYUpEnd()-1);
				if(ball.getIsDown())
					ball.setDirection(false,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
			
			else if(ball.getypos() == getYDownEnd() )//if the ball is inside the board(down)
			{
				ball.adjustYPosition(getYDownEnd()+1);
				if(!ball.getIsDown())
					ball.setDirection(false,true);
				if(Countdown == 0)
				{
					if(ball.getMaxDelay()>1)
					{
						ball.setMaxDelay(ball.getMaxDelay()-1);
					}
					Countdown = 9;
				}
				else
				{
					Countdown--;
				}
			}
		}
	}
}
bool Board::getIsLPlayer() const
{
	return isLPlayer;
}

void Board::setIsUp(bool in)
{
	isUp = in;
}
void Board::setIsDown(bool in)
{
	isDown = in;
}

void Board::setDelay(int c)
{
	Delay = c;
}

int Board::getDelay() const
{
	return Delay;
}

void Board::setCountDown(int c)
{
	Countdown = c;
}
int Board::getCountDown() const
{
	return Countdown;
}